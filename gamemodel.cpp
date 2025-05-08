#include "gamemodel.h"
#include <QRandomGenerator>
#include <QtMath>

/**
 * @file GameModel.cpp
 * @brief Implements the GameModel class, managing game logic and sequence handling.
 *
 * @author Siddharth Dhumal, Abdulrahman Al Hattali, Devin Gupta
 * @date 3/13/2025
 */

/**
 * @brief Constructs the GameModel object and initializes the game state.
 * @param parent Pointer to the parent QObject.
 */
GameModel::GameModel(QObject *parent)
    : QObject{parent}, m_playerIndex(0),
    m_isPlayingSequence(false),
    m_roundTimer(std::make_unique<QTimer>())
{
    m_roundTimer->setSingleShot(true);
    connect(m_roundTimer.get(), &QTimer::timeout, this, &GameModel::nextRound);
}

void GameModel::startGame()
{
    resetGame();
    m_sequence.append(QRandomGenerator::global()->bounded(2));
    playSequence();
}

void GameModel::processPlayerMove(int move)
{
    if(m_isPlayingSequence || m_sequence.isEmpty()) return;

    if(move == m_sequence[m_playerIndex]) {
        m_playerIndex++;

        const double progress = static_cast<double>(m_playerIndex) /
                                static_cast<double>(m_sequence.size()) * 100.0;
        emit progressUpdated(progress);

        if(m_playerIndex >= m_sequence.size()) {
            m_roundTimer->start(calculateDelay() * 1.5);
        }
    } else {
        emit gameOver();
    }
}

void GameModel::resetGame()
{
    m_sequence.clear();
    m_playerIndex = 0;
    m_roundTimer->stop();
    emit progressUpdated(0.0);
}

void GameModel::nextRound()
{
    m_sequence.append(QRandomGenerator::global()->bounded(2));
    m_playerIndex = 0;
    emit newRoundStarted();
    emit levelChanged(currentLevel());
    playSequence();
}

void GameModel::playSequence()
{
    m_isPlayingSequence = true;
    m_currentDelay = calculateDelay();
    emit sequenceStarted();

    for(int i = 0; i < m_sequence.size(); ++i) {
        QTimer::singleShot(i * m_currentDelay, this, [this, i] {
            emit sequenceStep(m_sequence[i]);
        });
    }

    QTimer::singleShot(m_sequence.size() * m_currentDelay, this, [this] {
        m_isPlayingSequence = false;
        emit sequenceFinished();
    });
}

int GameModel::calculateDelay() const
{
    return qBound(250, 1000 - static_cast<int>(50 * qLn(m_sequence.size() + 1)), 1000);
}
