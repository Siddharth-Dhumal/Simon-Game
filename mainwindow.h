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
     * @brief Handles the event when the green button is pressed.
     */
    void handleGreenButton();

    /**
     * @brief Handles the event when the yellow button is pressed.
     */
    void handleYellowButton();

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

    /**
     * @brief Toggles between light and dark mode when the theme action is clicked.
     */
    void onThemeClicked();

    /**
     * @brief Slot triggered when the level changes. Updates the level display label.
     * @param level The new game level.
     */
    void onLevelChanged(int level);

private:
    Ui::MainWindow *ui;     ///< Pointer to the UI elements.
    GameModel m_gameModel;  ///< Instance of the GameModel for game logic.
    QTimer m_flashTimer;    ///< Timer for handling button flashes.
    QString m_redStyle;     ///< Stores the red button style.
    QString m_blueStyle;    ///< Stores the blue button style.
    QString m_greenStyle;   ///< Stylesheet for the green button's default appearance.
    QString m_yellowStyle;  ///< Stylesheet for the yellow button's default appearance.
    QAction *m_toggleThemeAction;    ///< Action item for toggling between light and dark themes.
    bool m_darkMode;                 ///< Tracks whether dark mode is currently active.

    /**
     * @brief Applies the light mode stylesheet to the application UI.
     */
    void applyLightMode();

    /**
     * @brief Applies the dark mode stylesheet to the application UI.
     */
    void applyDarkMode();

    /**
     * @brief Updates the text label of the theme toggle action based on current mode.
     */
    void updateThemeButtonText();

    /**
     * @brief Sets the state of the buttons (enabled/disabled).
     * @param enabled True to enable buttons, false to disable them.
     */
    void setButtonState(bool enabled);
};

#endif // MAINWINDOW_H
