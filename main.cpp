#include "mainwindow.h"

#include <QApplication>

/**
 * @file main.cpp
 * @brief Entry point for the game application.
 */

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
