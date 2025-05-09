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
#include <QGraphicsDropShadowEffect>

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

    m_redStyle = R"(
QPushButton#redButton {
    background-color: rgb(200,50,50);
    border: 3px solid rgb(150,30,30);
    border-radius: 75px;
}
QPushButton#redButton:pressed {
    background-color: rgb(255,80,80);   /* slightly lighter */
    padding-top: 4px;                   /* simulate button moving down */
}
)";

    m_blueStyle = R"(
QPushButton#blueButton {
    background-color: rgb(50,50,200);
    border: 3px solid rgb(30,30,150);
    border-radius: 75px;
}
QPushButton#blueButton:pressed {
    background-color: rgb(120,120,255);
    padding-top: 4px;
}
)";

    m_greenStyle = R"(
QPushButton#greenButton {
    background-color: rgb(50,200,50);
    border: 3px solid rgb(30,150,30);
    border-radius: 75px;
}
QPushButton#greenButton:pressed {
    background-color: rgb(120,255,120);
    padding-top: 4px;
}
)";

    m_yellowStyle = R"(
QPushButton#yellowButton {
    background-color: rgb(241,196,15);
    border: 3px solid rgb(200,170,10);
    border-radius: 75px;
}
QPushButton#yellowButton:pressed {
    background-color: rgb(255,240,100);
    padding-top: 4px;
}
)";

    ui->redButton->setStyleSheet(m_redStyle);
    ui->blueButton->setStyleSheet(m_blueStyle);
    ui->greenButton->setStyleSheet(m_greenStyle);
    ui->yellowButton->setStyleSheet(m_yellowStyle);

    connect(ui->greenButton,  &QPushButton::clicked, this, &MainWindow::handleGreenButton);
    connect(ui->yellowButton, &QPushButton::clicked, this, &MainWindow::handleYellowButton);

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
    connect(&m_gameModel, &GameModel::sequenceStarted, this, &MainWindow::handleSequenceStart);
    connect(&m_gameModel, &GameModel::sequenceFinished, this, &MainWindow::handleSequenceEnd);
    connect(&m_gameModel, &GameModel::gameOver, this, &MainWindow::showGameOver);
    connect(&m_gameModel, &GameModel::progressUpdated, this, &MainWindow::updateProgress);
    connect(&m_gameModel, &GameModel::sequenceStep,
            this, &MainWindow::flashButton, Qt::QueuedConnection);
    connect(&m_gameModel, &GameModel::levelChanged,
            this,           &MainWindow::onLevelChanged);

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
    ui->levelLabel->setText("Level: 0");
    ui->scoreLabel->setText("Score: 0");
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

void MainWindow::handleGreenButton()
{
    m_gameModel.processPlayerMove(2);
}

void MainWindow::handleYellowButton()
{
    m_gameModel.processPlayerMove(3);
}

void MainWindow::flashButton(int button)
{
    QPushButton* target = nullptr;
    QString originalStyle;
    switch (button) {
    case 0: target = ui->redButton;    originalStyle = m_redStyle;    break;
    case 1: target = ui->blueButton;   originalStyle = m_blueStyle;   break;
    case 2: target = ui->greenButton;  originalStyle = m_greenStyle;  break;
    case 3: target = ui->yellowButton; originalStyle = m_yellowStyle; break;
    default: return;
    }

    QString flashStyle = originalStyle;
    switch (button) {
    case 0:
        flashStyle.replace("rgb(200,50,50)",  "rgb(255,120,120)", Qt::CaseInsensitive);
        break;
    case 1:
        flashStyle.replace("rgb(50,50,200)",  "rgb(120,120,255)", Qt::CaseInsensitive);
        break;
    case 2:
        flashStyle.replace("rgb(50,200,50)",  "rgb(120,255,120)", Qt::CaseInsensitive);
        break;
    case 3:
        flashStyle.replace("rgb(241,196,15)", "rgb(255,240,100)", Qt::CaseInsensitive);
        break;
    }

    target->setStyleSheet(flashStyle);

    QTimer::singleShot(200, this, [target, originalStyle]() {
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
    ui->greenButton->setEnabled(enabled);
    ui->yellowButton->setEnabled(enabled);

    ui->titleLabel->raise();
    ui->startButton->raise();
    ui->redButton->raise();
    ui->blueButton->raise();
    ui->greenButton->raise();
    ui->yellowButton->raise();

    const QString disabledStyle = "QPushButton:disabled { opacity: 0.5; }";
    ui->redButton->setStyleSheet(m_redStyle + disabledStyle);
    ui->blueButton->setStyleSheet(m_blueStyle + disabledStyle);
    ui->greenButton->setStyleSheet(m_greenStyle + disabledStyle);
    ui->yellowButton->setStyleSheet(m_yellowStyle + disabledStyle);
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
        /* Main background and text */
        QWidget#centralwidget {
            background-color: #FFFFFF;
            color: #000000;
        }

        /* Progress bar */
        QWidget#centralwidget QProgressBar {
            background-color: #DDDDDD;
            border: 1px solid #AAAAAA;
            border-radius: 5px;
            height: 16px;
        }
        QWidget#centralwidget QProgressBar::chunk {
            background-color: #409EFF;
            border-radius: 5px;
        }

        /* Labels inside centralwidget */
        QWidget#centralwidget QLabel {
            color: #000000;
        }

        /* Menu & status bars */
        QMenuBar, QStatusBar {
            background-color: transparent;
            color: #000000;
        }
    )";
    ui->centralwidget->setStyleSheet(light);
}

void MainWindow::applyDarkMode()
{
    static const QString dark = R"(
        /* Main background and text */
        QWidget#centralwidget {
            background-color: #2E2E2E;
            color: #FFFFFF;
        }

        /* Progress bar */
        QWidget#centralwidget QProgressBar {
            background-color: #555555;
            border: 1px solid #888888;
            border-radius: 5px;
            height: 16px;
        }
        QWidget#centralwidget QProgressBar::chunk {
            background-color: #66CCFF;
            border-radius: 5px;
        }

        /* Labels inside centralwidget */
        QWidget#centralwidget QLabel {
            color: #FFFFFF;
        }

        /* Menu & status bars */
        QMenuBar, QStatusBar {
            background-color: transparent;
            color: #FFFFFF;
        }
    )";
    ui->centralwidget->setStyleSheet(dark);
}

void MainWindow::onLevelChanged(int level)
{
    ui->levelLabel->setText(QString("Level: %1").arg(level));
    ui->scoreLabel->setText(QString("Score: %1").arg(level));
}
