//
// File: board.h
// Description: Manage the board in the Minimal Minesweeper, and all its related logic.
//

#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <array>
#include <SFML/System.hpp>
#include "config.h"
#include "config_internal.h"


class Board {

    // The following indicate which cells are mines, which have been flagged, and
    // which have been uncovered already.
    std::array<bool, TOTAL_CELLS> m_mines;
    std::array<bool, TOTAL_CELLS> m_flags;
    std::array<bool, TOTAL_CELLS> m_uncovered;

    int  m_numUncoveredCells   = 0;
    bool m_isGameOver          = false;
    bool m_isGameCompleted     = false;

    // clock is used to keep track of the game's elapsed time.
    sf::Clock m_clock;
    int m_gameStopTime = 0;

public:
    Board();

    // Members that don't affect the object's state
    bool isGameOver() const;
    bool isGameCompleted() const;
    bool isMine(int index) const;
    bool isFlagged(int index) const;
    bool isUncovered(int index) const;
    int  getGameElapsedSeconds() const;
    int  countNeighborMines(int x, int y) const;
    int  indexFromCellCoords(int x, int y) const;
    int  getNumberOfFlaggedNeighbors(int x, int y) const;
    std::vector<sf::Vector2u>   getNeighbors(int x, int y) const;

    // Members that affect the object's state
    void resetBoard();
    void flagCell(int x, int y);
    void calculateGameCompleted();
    void uncoverCell(int x, int y);
};

#endif // BOARD_H_
