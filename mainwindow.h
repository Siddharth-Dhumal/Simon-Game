#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include "gamemodel.h"
#include <QMenu>
#include <QAction>
#include <QSettings>
#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>
#include <QAbstractAnimation>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

/**
 * @file MainWindow.h
 * @brief Defines the MainWindow class, handling the GUI and user interactions.
 *
 * @author Siddharth Dhumal, Abdulrahman Al Hattali, Devin Gupta
 * @date 3/13/2025
 */

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    /**
     * @brief Constructs the MainWindow instance.
     * @param parent Pointer to the parent QWidget (default is nullptr).
     */
    MainWindow(QWidget *parent = nullptr);

    /**
     * @brief Destructor for MainWindow.
     */
    ~MainWindow();

private slots:

    /**
     * @brief Handles the event when the red button is pressed.
     */
    void handleRedButton();

    /**
     * @brief Handles the event when the blue button is pressed.
     */
    void handleBlueButton();

    /**
     * @brief Starts the game session.
     */
    void startGame();

    /**
     * @brief Flashes the specified button for visual feedback.
     * @param button The button to flash.
     */
    void flashButton(int button);

    /**
     * @brief Displays the game over screen.
     */
    void showGameOver();

    /**
     * @brief Updates the progress bar based on game progress.
     * @param progress The progress percentage.
     */
    void updateProgress(double progress);

    /**
     * @brief Handles the start of a sequence.
     */
    void handleSequenceStart();

    /**
     * @brief Handles the end of a sequence.
     */
    void handleSequenceEnd();
    void onThemeClicked();

private:
    Ui::MainWindow *ui;     ///< Pointer to the UI elements.
    GameModel m_gameModel;  ///< Instance of the GameModel for game logic.
    QTimer m_flashTimer;    ///< Timer for handling button flashes.
    QString m_redStyle;     ///< Stores the red button style.
    QString m_blueStyle;    ///< Stores the blue button style.
    QAction     *m_toggleThemeAction;
    void applyLightMode();
    void applyDarkMode();
    bool    m_darkMode;
    void    updateThemeButtonText();

    /**
     * @brief Sets the state of the buttons (enabled/disabled).
     * @param enabled True to enable buttons, false to disable them.
     */
    void setButtonState(bool enabled);
};

#endif // MAINWINDOW_H
