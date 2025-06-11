#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialogs/authdialog.h"
#include "dialogs/cryptodialog.h"
#include "dialogs/chordmethoddialog.h"
#include "dialogs/steganographydialog.h"
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setupUI();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupUI()
{
    // Создаем новые кликабельные фреймы
    cryptoCard = new ClickableFrame(this);
    chordCard = new ClickableFrame(this);
    steganoCard = new ClickableFrame(this);
    
    // Создаем новые лейблы для наших кликабельных фреймов
    QLabel* cryptoIcon = new QLabel(cryptoCard);
    QLabel* cryptoTitle = new QLabel(cryptoCard);
    QLabel* cryptoDesc = new QLabel(cryptoCard);
    
    QLabel* chordIcon = new QLabel(chordCard);
    QLabel* chordTitle = new QLabel(chordCard);
    QLabel* chordDesc = new QLabel(chordCard);
    
    QLabel* steganoIcon = new QLabel(steganoCard);
    QLabel* steganoTitle = new QLabel(steganoCard);
    QLabel* steganoDesc = new QLabel(steganoCard);
    
    // Копируем свойства из оригинальных лейблов
    cryptoIcon->setMinimumSize(ui->cryptoIconLabel->minimumSize());
    cryptoIcon->setMaximumSize(ui->cryptoIconLabel->maximumSize());
    cryptoIcon->setPixmap(ui->cryptoIconLabel->pixmap(Qt::ReturnByValue));
    cryptoIcon->setScaledContents(ui->cryptoIconLabel->hasScaledContents());
    cryptoIcon->setAlignment(ui->cryptoIconLabel->alignment());
    
    cryptoTitle->setFont(ui->cryptoCardTitle->font());
    cryptoTitle->setStyleSheet(ui->cryptoCardTitle->styleSheet());
    cryptoTitle->setText(ui->cryptoCardTitle->text());
    cryptoTitle->setAlignment(ui->cryptoCardTitle->alignment());
    
    cryptoDesc->setText(ui->cryptoCardDesc->text());
    cryptoDesc->setAlignment(ui->cryptoCardDesc->alignment());
    cryptoDesc->setWordWrap(ui->cryptoCardDesc->wordWrap());
    
    // Копируем свойства для хорд карточки
    chordIcon->setMinimumSize(ui->chordIconLabel->minimumSize());
    chordIcon->setMaximumSize(ui->chordIconLabel->maximumSize());
    chordIcon->setPixmap(ui->chordIconLabel->pixmap(Qt::ReturnByValue));
    chordIcon->setScaledContents(ui->chordIconLabel->hasScaledContents());
    chordIcon->setAlignment(ui->chordIconLabel->alignment());
    
    chordTitle->setFont(ui->chordCardTitle->font());
    chordTitle->setStyleSheet(ui->chordCardTitle->styleSheet());
    chordTitle->setText(ui->chordCardTitle->text());
    chordTitle->setAlignment(ui->chordCardTitle->alignment());
    
    chordDesc->setText(ui->chordCardDesc->text());
    chordDesc->setAlignment(ui->chordCardDesc->alignment());
    chordDesc->setWordWrap(ui->chordCardDesc->wordWrap());
    
    // Копируем свойства для стеганографии карточки
    steganoIcon->setMinimumSize(ui->steganoIconLabel->minimumSize());
    steganoIcon->setMaximumSize(ui->steganoIconLabel->maximumSize());
    steganoIcon->setPixmap(ui->steganoIconLabel->pixmap(Qt::ReturnByValue));
    steganoIcon->setScaledContents(ui->steganoIconLabel->hasScaledContents());
    steganoIcon->setAlignment(ui->steganoIconLabel->alignment());
    
    steganoTitle->setFont(ui->steganoCardTitle->font());
    steganoTitle->setStyleSheet(ui->steganoCardTitle->styleSheet());
    steganoTitle->setText(ui->steganoCardTitle->text());
    steganoTitle->setAlignment(ui->steganoCardTitle->alignment());
    
    steganoDesc->setText(ui->steganoCardDesc->text());
    steganoDesc->setAlignment(ui->steganoCardDesc->alignment());
    steganoDesc->setWordWrap(ui->steganoCardDesc->wordWrap());
    
    // Настраиваем стили и параметры для наших новых фреймов
    cryptoCard->setObjectName("cryptoCard");
    cryptoCard->setMinimumSize(ui->cryptoCard->minimumSize());
    cryptoCard->setStyleSheet(ui->cryptoCard->styleSheet());
    cryptoCard->setCursor(Qt::PointingHandCursor);
    
    chordCard->setObjectName("chordCard");
    chordCard->setMinimumSize(ui->chordCard->minimumSize());
    chordCard->setStyleSheet(ui->chordCard->styleSheet());
    chordCard->setCursor(Qt::PointingHandCursor);
    
    steganoCard->setObjectName("steganoCard");
    steganoCard->setMinimumSize(ui->steganoCard->minimumSize());
    steganoCard->setStyleSheet(ui->steganoCard->styleSheet());
    steganoCard->setCursor(Qt::PointingHandCursor);
    
    // Создаем и настраиваем лейауты для наших фреймов
    QVBoxLayout* cryptoLayout = new QVBoxLayout(cryptoCard);
    cryptoLayout->addWidget(cryptoIcon);
    cryptoLayout->addWidget(cryptoTitle);
    cryptoLayout->addWidget(cryptoDesc);
    
    QVBoxLayout* chordLayout = new QVBoxLayout(chordCard);
    chordLayout->addWidget(chordIcon);
    chordLayout->addWidget(chordTitle);
    chordLayout->addWidget(chordDesc);
    
    QVBoxLayout* steganoLayout = new QVBoxLayout(steganoCard);
    steganoLayout->addWidget(steganoIcon);
    steganoLayout->addWidget(steganoTitle);
    steganoLayout->addWidget(steganoDesc);
    
    // Скрываем оригинальные фреймы и добавляем наши
    ui->cryptoCard->setVisible(false);
    ui->chordCard->setVisible(false);
    ui->steganoCard->setVisible(false);
    
    ui->cardsLayout->addWidget(cryptoCard);
    ui->cardsLayout->addWidget(chordCard);
    ui->cardsLayout->addWidget(steganoCard);
    
    // Подключаем сигналы к слотам
    connect(cryptoCard, &ClickableFrame::clicked, this, &MainWindow::on_actionCrypto_triggered);
    connect(chordCard, &ClickableFrame::clicked, this, &MainWindow::on_actionChordMethod_triggered);
    connect(steganoCard, &ClickableFrame::clicked, this, &MainWindow::on_actionSteganography_triggered);
}

void MainWindow::on_actionCrypto_triggered()
{
    CryptoDialog dialog(this);
    dialog.exec();
}

void MainWindow::on_actionChordMethod_triggered()
{
    ChordMethodDialog dialog(this);
    dialog.exec();
}

void MainWindow::on_actionSteganography_triggered()
{
    SteganographyDialog dialog(this);
    dialog.exec();
}

void MainWindow::on_cryptoButton_clicked()
{
    on_actionCrypto_triggered();
}

void MainWindow::on_chordMethodButton_clicked()
{
    on_actionChordMethod_triggered();
}

void MainWindow::on_steganographyButton_clicked()
{
    on_actionSteganography_triggered();
}

void MainWindow::setUsername(const QString &username)
{
    m_username = username;
    
    // Update user label in sidebar
    ui->userLabel->setText(m_username);
    
    // Update window title
    setWindowTitle(tr("Титкин Степан Андреевич 241-351 - Пользователь: %1").arg(username));
} 