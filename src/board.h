//
// File: board.h
// Description: Manage the board in the Minimal Minesweeper, and all its related logic.
//

#pragma once

#include <vector>
#include <array>
#include <SFML/System.hpp>
#include "config.h"
#include "config_internal.h"


class Board {

    std::array<bool, TOTAL_CELLS> mines;
    std::array<bool, TOTAL_CELLS> flags;
    std::array<bool, TOTAL_CELLS> uncovered;

    bool m_isGameOver       = false;
    bool m_isGameCompleted  = false;
    int numUncoveredCells   = 0;

    sf::Clock clock;
    int gameStopTime = 0;

public:
    Board();
    int indexFromCellCoords(int x, int y);
    int getNumberOfFlaggedNeighbors(int x, int y);
    int countNeighborMines(int x, int y);
    bool isUncovered(int index);
    bool isMine(int index);
    bool isFlagged(int index);
    bool isGameOver();
    bool isGameCompleted();
    void uncoverCell(int x, int y);
    void calculateGameCompleted();
    void resetBoard();
    void flagCell(int x, int y);
    std::vector<sf::Vector2u>   getNeighbors(int x, int y);
    int getGameElapsedSeconds();

};


