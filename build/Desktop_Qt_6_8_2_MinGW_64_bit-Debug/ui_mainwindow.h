/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *mainLayout;
    QHBoxLayout *titleLayout;
    QLabel *titleLabel;
    QSpacerItem *horizontalSpacer;
    QPushButton *themeToggle;
    QGridLayout *gridLayout;
    QPushButton *redButton;
    QPushButton *blueButton;
    QPushButton *greenButton;
    QPushButton *yellowButton;
    QPushButton *startButton;
    QProgressBar *progressBar;
    QHBoxLayout *levelScoreLayout;
    QLabel *levelLabel;
    QLabel *scoreLabel;
    QLabel *statusLabel;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(600, 800);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        mainLayout = new QVBoxLayout(centralwidget);
        mainLayout->setObjectName("mainLayout");
        titleLayout = new QHBoxLayout();
        titleLayout->setObjectName("titleLayout");
        titleLabel = new QLabel(centralwidget);
        titleLabel->setObjectName("titleLabel");
        titleLabel->setAlignment(Qt::AlignCenter);
        QFont font;
        font.setFamilies({QString::fromUtf8("Sans Serif")});
        font.setPointSize(32);
        font.setBold(true);
        titleLabel->setFont(font);

        titleLayout->addWidget(titleLabel);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        titleLayout->addItem(horizontalSpacer);

        themeToggle = new QPushButton(centralwidget);
        themeToggle->setObjectName("themeToggle");
        themeToggle->setStyleSheet(QString::fromUtf8("QPushButton#themeToggle { background: none; border: none; font: bold 14px; }\n"
"QPushButton#themeToggle:hover { color: #2980B9; }\n"
""));
        themeToggle->setMinimumSize(QSize(120, 30));

        titleLayout->addWidget(themeToggle);


        mainLayout->addLayout(titleLayout);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName("gridLayout");
        gridLayout->setHorizontalSpacing(20);
        gridLayout->setVerticalSpacing(20);
        redButton = new QPushButton(centralwidget);
        redButton->setObjectName("redButton");
        redButton->setMinimumSize(QSize(150, 150));
        redButton->setStyleSheet(QString::fromUtf8("border-radius: 75px; background-color: #E74C3C; border: none; font: bold 18px;"));

        gridLayout->addWidget(redButton, 0, 0, 1, 1);

        blueButton = new QPushButton(centralwidget);
        blueButton->setObjectName("blueButton");
        blueButton->setMinimumSize(QSize(150, 150));
        blueButton->setStyleSheet(QString::fromUtf8("border-radius: 75px; background-color: #3498DB; border: none; font: bold 18px;"));

        gridLayout->addWidget(blueButton, 0, 1, 1, 1);

        greenButton = new QPushButton(centralwidget);
        greenButton->setObjectName("greenButton");
        greenButton->setMinimumSize(QSize(150, 150));
        greenButton->setStyleSheet(QString::fromUtf8("border-radius: 75px; background-color: #2ECC71; border: none; font: bold 18px;"));

        gridLayout->addWidget(greenButton, 1, 0, 1, 1);

        yellowButton = new QPushButton(centralwidget);
        yellowButton->setObjectName("yellowButton");
        yellowButton->setMinimumSize(QSize(150, 150));
        yellowButton->setStyleSheet(QString::fromUtf8("border-radius: 75px; background-color: #F1C40F; border: none; font: bold 18px;"));

        gridLayout->addWidget(yellowButton, 1, 1, 1, 1);


        mainLayout->addLayout(gridLayout);

        startButton = new QPushButton(centralwidget);
        startButton->setObjectName("startButton");
        startButton->setStyleSheet(QString::fromUtf8("QPushButton { background-color: #34495E; border-radius: 10px; color: white; font: bold 16px; }\n"
"QPushButton:hover { background-color: #5D6D7E; }"));
        startButton->setMinimumHeight(50);

        mainLayout->addWidget(startButton);

        progressBar = new QProgressBar(centralwidget);
        progressBar->setObjectName("progressBar");
        progressBar->setTextVisible(false);
        progressBar->setMinimumHeight(20);

        mainLayout->addWidget(progressBar);

        levelScoreLayout = new QHBoxLayout();
        levelScoreLayout->setSpacing(40);
        levelScoreLayout->setObjectName("levelScoreLayout");
        levelLabel = new QLabel(centralwidget);
        levelLabel->setObjectName("levelLabel");
        QFont font1;
        font1.setPointSize(14);
        font1.setBold(true);
        levelLabel->setFont(font1);

        levelScoreLayout->addWidget(levelLabel);

        scoreLabel = new QLabel(centralwidget);
        scoreLabel->setObjectName("scoreLabel");
        scoreLabel->setFont(font1);

        levelScoreLayout->addWidget(scoreLabel);


        mainLayout->addLayout(levelScoreLayout);

        statusLabel = new QLabel(centralwidget);
        statusLabel->setObjectName("statusLabel");
        statusLabel->setAlignment(Qt::AlignCenter);
        QFont font2;
        font2.setPointSize(12);
        statusLabel->setFont(font2);
        statusLabel->setMinimumHeight(30);

        mainLayout->addWidget(statusLabel);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Simon Says", nullptr));
        titleLabel->setText(QCoreApplication::translate("MainWindow", "Simon Says", nullptr));
        themeToggle->setText(QCoreApplication::translate("MainWindow", "\360\237\214\231 Dark Mode", nullptr));
        startButton->setText(QCoreApplication::translate("MainWindow", "Start Game", nullptr));
        levelLabel->setText(QCoreApplication::translate("MainWindow", "Level: 0", nullptr));
        scoreLabel->setText(QCoreApplication::translate("MainWindow", "Score: 0", nullptr));
        statusLabel->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
