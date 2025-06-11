#include "chordmethod.h"
#include <cmath>
#include <QRegularExpression>

ChordMethod::ChordMethod() {
}

ChordMethod::Result ChordMethod::solveEquation(const QString &equation, double a, double b, double epsilon, int maxIterations) {
    bool success = false;
    QString errorMessage;
    
    auto func = parseEquation(equation, success, errorMessage);
    
    if (!success) {
        Result result;
        result.success = false;
        result.errorMessage = errorMessage;
        return result;
    }
    
    return solve(func, a, b, epsilon, maxIterations);
}

ChordMethod::Result ChordMethod::solve(const std::function<double(double)> &func, double a, double b, double epsilon, int maxIterations) {
    Result result;
    result.success = false;
    result.iterations = 0;
    result.precision = epsilon;
    
    double fa = func(a);
    double fb = func(b);
    
    if (fa * fb > 0) {
        result.errorMessage = "Функция должна иметь разные знаки на концах интервала";
        return result;
    }
    
    double c = a;
    double fc;
    
    for (int i = 0; i < maxIterations; ++i) {
        double denominator = fb - fa;
        if (std::abs(denominator) < 1e-10) {
            result.errorMessage = "Деление на ноль в методе хорд";
            return result;
        }
        
        c = a - fa * (b - a) / denominator;
        fc = func(c);
        
        result.iterations++;
        
        if (std::abs(fc) < epsilon) {
            result.success = true;
            result.root = c;
            return result;
        }
        
        if (fa * fc < 0) {
            b = c;
            fb = fc;
        } else {
            a = c;
            fa = fc;
        }
        
        if (std::abs(b - a) < epsilon) {
            result.success = true;
            result.root = c;
            return result;
        }
    }
    
    result.errorMessage = "Превышено максимальное число итераций";
    return result;
}

std::function<double(double)> ChordMethod::parseEquation(const QString &equation, bool &success, QString &errorMessage) {
    QString normalizedEquation = equation.simplified().replace(" ", "");
    
    QRegularExpression regex("([+-]?\\d*\\.?\\d*)\\*?x\\^2\\s*([+-]\\d*\\.?\\d*)\\*?x\\s*([+-]\\d*\\.?\\d*)");
    QRegularExpressionMatch match = regex.match(normalizedEquation);
    
    if (match.hasMatch()) {
        QString aStr = match.captured(1);
        double a = 1.0;
        if (!aStr.isEmpty()) {
            if (aStr == "-") {
                a = -1.0;
            } else if (aStr != "+") {
                a = aStr.toDouble(&success);
                if (!success) {
                    errorMessage = "Не удалось преобразовать коэффициент a: " + aStr;
                    return [](double) -> double { return 0.0; };
                }
            }
        }
        
        QString bStr = match.captured(2);
        double b = 0.0;
        if (!bStr.isEmpty()) {
            if (bStr == "-") {
                b = -1.0;
            } else if (bStr == "+") {
                b = 1.0;
            } else {
                b = bStr.toDouble(&success);
                if (!success) {
                    errorMessage = "Не удалось преобразовать коэффициент b: " + bStr;
                    return [](double) -> double { return 0.0; };
                }
            }
        }
        
        QString cStr = match.captured(3);
        double c = 0.0;
        if (!cStr.isEmpty()) {
            if (cStr == "-") {
                c = -1.0;
            } else if (cStr == "+") {
                c = 1.0;
            } else {
                c = cStr.toDouble(&success);
                if (!success) {
                    errorMessage = "Не удалось преобразовать коэффициент c: " + cStr;
                    return [](double) -> double { return 0.0; };
                }
            }
        }
        
        success = true;
        return [a, b, c](double x) -> double {
            return a * x * x + b * x + c;
        };
    } 
    
    QRegularExpression linearRegex("([+-]?\\d*\\.?\\d*)\\*?x\\s*([+-]\\d*\\.?\\d*)");
    QRegularExpressionMatch linearMatch = linearRegex.match(normalizedEquation);
    
    if (linearMatch.hasMatch()) {
        QString aStr = linearMatch.captured(1);
        double a = 1.0;
        if (!aStr.isEmpty()) {
            if (aStr == "-") {
                a = -1.0;
            } else if (aStr != "+") {
                a = aStr.toDouble(&success);
                if (!success) {
                    errorMessage = "Не удалось преобразовать коэффициент a: " + aStr;
                    return [](double) -> double { return 0.0; };
                }
            }
        }
        
        QString bStr = linearMatch.captured(2);
        double b = 0.0;
        if (!bStr.isEmpty()) {
            if (bStr == "-") {
                b = -1.0;
            } else if (bStr == "+") {
                b = 1.0;
            } else {
                b = bStr.toDouble(&success);
                if (!success) {
                    errorMessage = "Не удалось преобразовать коэффициент b: " + bStr;
                    return [](double) -> double { return 0.0; };
                }
            }
        }
        
        success = true;
        return [a, b](double x) -> double {
            return a * x + b;
        };
    }
    
    success = false;
    errorMessage = "Не удалось распознать уравнение. Поддерживаются форматы: ax^2 + bx + c или ax + b";
    return [](double) -> double { return 0.0; };
} 