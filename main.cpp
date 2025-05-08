#include "mainwindow.h"

#include <QApplication>

/**
 * @file main.cpp
 * @brief Entry point for the game application.
 *
 * @author Siddharth Dhumal, Abdulrahman Al Hattali, Devin Gupta
 * @date 3/13/2025
 *
 * @team_members
 * - Siddharth Dhumal (GitHub: Siddharth-Dhumal)
 * - Abdulrahman Al Hattali (GitHub: HATTALI)
 * - Devin Gupta (GitHub: devingupta1)
 *
 * @repository
 * GitHub URL: https://github.com/UofU-CS3505/cs3505-assignment6-Siddharth-Dhumal
 *
 * @creative_feature
 * The background color changes dynamically whenever the player moves to the next level,
 * adding a visually engaging and immersive experience.
 */

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
