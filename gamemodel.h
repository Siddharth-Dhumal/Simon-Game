#ifndef GAMEMODEL_H
#define GAMEMODEL_H

#include <QObject>
#include <QVector>
#include <QTimer>
#include <memory>

/**
 * @file GameModel.h
 * @brief Defines the GameModel class, handling game logic and state management.
 */

class GameModel : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief Constructs a GameModel instance.
     * @param parent Pointer to the parent QObject (default is nullptr).
     */
    explicit GameModel(QObject *parent = nullptr);

    /**
     * @brief Starts a new game session.
     */
    void startGame();

    /**
     * @brief Processes a player's move.
     * @param move The player's move input.
     */
    void processPlayerMove(int move);

    /**
     * @brief Resets the game state.
     */
    void resetGame();

    /**
     * @brief Gets the current game score.
     * @return The current score based on the sequence length.
     */
    int getScore() const { return m_sequence.isEmpty() ? 0 : m_sequence.size() - 1; }

    /**
     * @brief Gets the current delay between sequence steps.
     * @return The delay in milliseconds.
     */
    int currentDelay() const { return m_currentDelay; }

    /**
     * @brief Gets the current level of the game.
     * @return The current level based on sequence length.
     */
    int currentLevel() const { return m_sequence.isEmpty() ? 0 : m_sequence.size() - 1; }

signals:
    void sequenceStep(int step); ///< Emitted when a sequence step occurs.
    void sequenceStarted();     ///< Emitted when the sequence starts.
    void sequenceFinished();    ///< Emitted when the sequence ends.
    void gameOver();            ///< Emitted when the game ends.
    void progressUpdated(double progress);///< Emitted when progress is updated.
    void levelChanged(int level); ///< Emitted when the game level changes.
    void newRoundStarted();     ///< Emitted when a new round begins.

private slots:

    /**
     * @brief Proceeds to the next round in the game.
     */
    void nextRound();

private:
    QVector<int> m_sequence; ///< Stores the sequence of moves.
    int m_playerIndex;      ///< Tracks the player's current position in the sequence.
    bool m_isPlayingSequence; ///< Indicates if the game is currently playing a sequence.
    std::unique_ptr<QTimer> m_roundTimer; ///< Timer for managing sequence timing.
    int m_currentDelay;     ///< Current delay duration for sequence steps.

    /**
     * @brief Plays the stored sequence for the player.
     */
    void playSequence();

    /**
     * @brief Calculates the delay between sequence steps based on the level.
     * @return The computed delay in milliseconds.
     */
    int calculateDelay() const;
};

#endif // GAMEMODEL_H
