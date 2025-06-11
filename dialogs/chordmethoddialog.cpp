#include "chordmethoddialog.h"
#include "ui_chordmethoddialog.h"
#include <QMessageBox>

ChordMethodDialog::ChordMethodDialog(QWidget *parent) : QDialog(parent), ui(new Ui::ChordMethodDialog) {
    ui->setupUi(this);
    
    m_client = ClientSingleton::getInstance();
    
    ui->equationEdit->setText("x^2 -4*x +3");
    ui->aSpinBox->setValue(0);
    ui->bSpinBox->setValue(5);
    ui->epsilonSpinBox->setValue(0.0001);
    ui->maxIterationsSpinBox->setValue(100);
}

ChordMethodDialog::~ChordMethodDialog() {
    delete ui;
}

void ChordMethodDialog::on_solveButton_clicked() {
    QString equation = ui->equationEdit->text();
    double a = ui->aSpinBox->value();
    double b = ui->bSpinBox->value();
    double epsilon = ui->epsilonSpinBox->value();
    int maxIterations = ui->maxIterationsSpinBox->value();
    
    if (equation.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Уравнение не может быть пустым");
        return;
    }
    
    if (a >= b) {
        QMessageBox::warning(this, "Ошибка", "Значение a должно быть меньше значения b");
        return;
    }
    
    Protocol::Response response = m_client->solveEquation(equation, a, b, epsilon, maxIterations);
    
    if (response.status() == Protocol::ResponseStatus::SUCCESS) {
        double root = response.data("root").toDouble();
        int iterations = response.data("iterations").toInt();
        double precision = response.data("precision").toDouble();
        
        ui->resultEdit->setText(QString("Корень: %1\nИтераций: %2\nТочность: %3")
                               .arg(root, 0, 'f', 8)
                               .arg(iterations)
                               .arg(precision, 0, 'e', 4));
    } else {
        ui->resultEdit->setText("Ошибка: " + response.errorMessage());
    }
}

void ChordMethodDialog::on_clearButton_clicked() {
    ui->equationEdit->clear();
    ui->resultEdit->clear();
    ui->aSpinBox->setValue(0);
    ui->bSpinBox->setValue(0);
    ui->epsilonSpinBox->setValue(0.0001);
    ui->maxIterationsSpinBox->setValue(100);
} 