#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QPushButton>
#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>
#include <QAbstractAnimation>
#include <QMenu>
#include <QAction>
#include <QSettings>
#include <QApplication>

/**
 * @file MainWindow.cpp
 * @brief Implements the MainWindow class, handling GUI interactions and game events.
 */

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_gameModel(this)
    , m_flashTimer(this)
    , m_darkMode(false)
{
    ui->setupUi(this);

    ui->titleLabel->setStyleSheet(
        "QLabel {"
        "   background-color: rgba(255, 255, 255, 220);"
        "   color: black;"
        "   border-radius: 8px;"
        "   padding: 8px 15px;"
        "   border: 2px solid rgba(0, 0, 0, 100);"
        "   font: bold 24px;"
        "}");

    ui->startButton->setStyleSheet(
        "QPushButton {"
        "   background-color: rgba(255, 255, 255, 220);"
        "   color: black;"
        "   border-radius: 10px;"
        "   padding: 10px;"
        "   border: 2px solid rgba(0, 0, 0, 100);"
        "   font: bold 14px;"
        "}"
        "QPushButton:hover {"
        "   background-color: rgba(255, 255, 255, 255);"
        "   border: 2px solid rgba(0, 0, 0, 150);"
        "}");

    m_redStyle = "QPushButton {"
                 "background-color: rgb(200, 50, 50);"
                 "border: 3px solid rgb(150, 30, 30);"
                 "border-radius: 15px;"
                 "color: white;"
                 "font: bold 18px;"
                 "}";

    m_blueStyle = "QPushButton {"
                  "background-color: rgb(50, 50, 200);"
                  "border: 3px solid rgb(30, 30, 150);"
                  "border-radius: 15px;"
                  "color: white;"
                  "font: bold 18px;"
                  "}";

    ui->redButton->setStyleSheet(m_redStyle);
    ui->blueButton->setStyleSheet(m_blueStyle);

    connect(ui->redButton, &QPushButton::clicked, this, &MainWindow::handleRedButton);
    connect(ui->blueButton, &QPushButton::clicked, this, &MainWindow::handleBlueButton);
    connect(ui->startButton, &QPushButton::clicked, this, &MainWindow::startGame);
    connect(ui->themeToggle, &QPushButton::clicked,
            this, &MainWindow::onThemeClicked);

    QSettings settings("YourCompany", "SimonSays");
    bool dark = settings.value("darkMode", false).toBool();
    m_darkMode = dark;
    if(dark) applyDarkMode(); else applyLightMode();
    updateThemeButtonText();
    connect(&m_gameModel, &GameModel::sequenceStep, this, &MainWindow::flashButton);
    connect(&m_gameModel, &GameModel::sequenceStarted, this, &MainWindow::handleSequenceStart);
    connect(&m_gameModel, &GameModel::sequenceFinished, this, &MainWindow::handleSequenceEnd);
    connect(&m_gameModel, &GameModel::gameOver, this, &MainWindow::showGameOver);
    connect(&m_gameModel, &GameModel::progressUpdated, this, &MainWindow::updateProgress);
    connect(&m_gameModel, &GameModel::sequenceStep,
            this, &MainWindow::flashButton, Qt::QueuedConnection);

    setButtonState(false);
    ui->progressBar->setValue(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::startGame()
{
    ui->startButton->setEnabled(false);
    setButtonState(false);
    m_gameModel.startGame();
}

void MainWindow::handleRedButton()
{
    m_gameModel.processPlayerMove(0);
}

void MainWindow::handleBlueButton()
{
    m_gameModel.processPlayerMove(1);
}

void MainWindow::flashButton(int button)
{
    QPushButton* target = button == 0 ? ui->redButton : ui->blueButton;

    const QString originalStyle = (button == 0) ? m_redStyle : m_blueStyle;

    QString flashStyle = originalStyle;
    flashStyle.replace("200, 50, 50", "255, 120, 120", Qt::CaseInsensitive);
    flashStyle.replace("50, 50, 200", "120, 120, 255", Qt::CaseInsensitive);

    target->setStyleSheet(flashStyle);

    const int flashDuration = static_cast<int>(m_gameModel.currentDelay() * 0.7);

    QTimer::singleShot(flashDuration, target, [target, originalStyle] {
        target->setStyleSheet(originalStyle);
    });
}

void MainWindow::showGameOver()
{
    QMessageBox::information(this, "Game Over", "Sequence failed! Your score: " +
                                                    QString::number(m_gameModel.getScore()));
    ui->startButton->setEnabled(true);
    setButtonState(false);
}

void MainWindow::updateProgress(double progress)
{
    ui->progressBar->setValue(static_cast<int>(progress));
}

void MainWindow::handleSequenceStart()
{
    setButtonState(false);
    ui->progressBar->setValue(0);
}

void MainWindow::handleSequenceEnd()
{
    setButtonState(true);
}

void MainWindow::setButtonState(bool enabled)
{
    ui->redButton->setEnabled(enabled);
    ui->blueButton->setEnabled(enabled);

    ui->titleLabel->raise();
    ui->startButton->raise();
    ui->redButton->raise();
    ui->blueButton->raise();

    const QString disabledStyle = "QPushButton:disabled { opacity: 0.5; }";
    ui->redButton->setStyleSheet(m_redStyle + disabledStyle);
    ui->blueButton->setStyleSheet(m_blueStyle + disabledStyle);
}

void MainWindow::updateThemeButtonText() {
    if(m_darkMode)
        ui->themeToggle->setText("☀️ Light Mode");
    else
        ui->themeToggle->setText("🌙 Dark Mode");
}

void MainWindow::onThemeClicked() {
    m_darkMode = !m_darkMode;
    QSettings("YourCompany", "SimonSays").setValue("darkMode", m_darkMode);
    if(m_darkMode) applyDarkMode(); else applyLightMode();
    updateThemeButtonText();
}

void MainWindow::applyLightMode()
{
    static const QString light = R"(
        QWidget {
            background-color: #FFFFFF;
            color: #000000;
        }
        QPushButton {
            background-color: #F0F0F0;
            color: #000000;
            border: none;
            border-radius: 5px;
            padding: 8px;
        }
        QPushButton:hover {
            background-color: #E0E0E0;
        }
        QProgressBar {
            background-color: #DDDDDD;
            border: 1px solid #AAAAAA;
            border-radius: 5px;
            height: 16px;
        }
        QProgressBar::chunk {
            background-color: #409EFF;
            border-radius: 5px;
        }
    )";
    qApp->setStyleSheet(light);
}

void MainWindow::applyDarkMode()
{
    static const QString dark = R"(
        QWidget {
            background-color: #2E2E2E;
            color: #FFFFFF;
        }
        QPushButton {
            background-color: #444444;
            color: #FFFFFF;
            border: 1px solid #888888;
            border-radius: 5px;
            padding: 8px;
        }
        QPushButton:hover {
            border: 1px solid #CCCCCC;
        }
        QProgressBar {
            background-color: #555555;
            border: 1px solid #888888;
            border-radius: 5px;
            height: 16px;
        }
        QProgressBar::chunk {
            background-color: #66CCFF;
            border-radius: 5px;
        }
    )";
    qApp->setStyleSheet(dark);
}
