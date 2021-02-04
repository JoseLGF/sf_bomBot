#include "config.h"
#include "board.h"

using namespace std;

int Board::indexFromCellCoords(int x, int y) const {
    return ((y*NUM_COLS) + x);
}

vector<sf::Vector2u> Board::getNeighbors(int x, int y) const {
    vector<sf::Vector2u> out;
    for(int i=x-1; i<=x+1; i++){
    for(int j=y+1; j>=y-1; j--){
        if(
            (i < 0)            || // ignore squares out of grid dimensions
            (i > (NUM_COLS-1)) ||
            (j < 0)            ||
            (j > (NUM_ROWS-1)) || 
            ((i==x) && (j==y))    // ignore center square
        )
        {
            continue;
        }
        out.push_back(sf::Vector2u(i, j));
    }
    }
    return out;
}

int Board::countNeighborMines(int x, int y) const {
    int counter = 0;
    vector<sf::Vector2u> neighbors = getNeighbors(x, y);
    for(auto neighbor: neighbors){
        if(m_mines[indexFromCellCoords(neighbor.x, neighbor.y)]){
            counter++;
        }
    }

    return counter;
}

void Board::uncoverCell(int x, int y){

    int index = indexFromCellCoords(x, y);

    // Avoid uncovering if...
    if(
        m_isGameOver            ||
        m_isGameCompleted       ||
        m_uncovered[index]        || // Cell has been previously uncovered
        m_flags[index]            || // Cell has been flagged
        (index >= TOTAL_CELLS)         // index exceeds grid dimensions
    )
    {
        return;
    }

    // Avoids making the player lose on their first move.
    // Also detect player first move to start time count
    if(m_numUncoveredCells == 0){
        m_clock.restart();
        m_mines[index] = false;
    }

    // Uncover this cell
    m_uncovered[index] = true;
    m_numUncoveredCells++;
    calculateGameCompleted();

    // If uncovered cell contains a mine, game over
    if(m_mines[index]){
        m_isGameOver = true;
        m_gameStopTime = m_clock.getElapsedTime().asSeconds();
        return;
    }

    // Checks if we can propagate
    if(countNeighborMines(x, y) > 0){
        return;
    }

    // propagate cells
    for(auto neighbor: getNeighbors(x, y)) {
        uncoverCell(neighbor.x, neighbor.y);
    }

}

void Board::calculateGameCompleted() {
    int numOfNonMines = count(m_mines.begin(), m_mines.end(), false);
    if((m_numUncoveredCells == numOfNonMines) && !m_isGameOver){
        // winning time is captured only once
        if(!m_isGameCompleted){m_gameStopTime = m_clock.getElapsedTime().asSeconds();}
        m_isGameCompleted = true;
    }
}

void Board::resetBoard() {
    // variables are (void)'ed in order to prevent compiler's unused warning
    for(auto& mine: m_mines)     { mine = false; (void)mine;}
    for(auto& flag: m_flags)     { flag = false; (void)flag;}
    for(auto& cell: m_uncovered) { cell = false; (void)cell;}

    // Initialize mines
    srand (time(NULL));
    //srand(1);
    for(auto& mine: m_mines){
        mine = !(rand() % GAME_CELLTOMINERATIO);
        (void)mine;
    }

    m_numUncoveredCells   = 0;
    m_isGameOver          = false;
    m_isGameCompleted     = false;
}

void Board::flagCell(int x, int y) {
    int index = NUM_COLS*y + x;
    // don't flag this cell if...
    if(
        m_isGameOver            ||
        m_isGameCompleted       ||
        index >= TOTAL_CELLS    || // index exceeds grid dimensions
        m_uncovered[index]         // cell has already been uncovered
    )
    {
        return;
    }

    m_flags[index] = !m_flags[index];

}

int Board::getNumberOfFlaggedNeighbors(int x, int y) const {
    int flaggedNeighbors = 0;
    vector<sf::Vector2u> neighbors = getNeighbors(x, y);

    for(auto neighbor: neighbors){
        int neighborIndex = indexFromCellCoords(neighbor.x, neighbor.y);
        if(m_flags[neighborIndex]){
            flaggedNeighbors++;
        }
    }

    return flaggedNeighbors;
}

Board::Board(){
    resetBoard();
}

bool Board::isUncovered(int index) const {
    return m_uncovered[index];
}

bool Board::isMine(int index) const {
    return m_mines[index];
}

bool Board::isGameOver() const {
	return m_isGameOver;
}

bool Board::isGameCompleted() const {
	return m_isGameCompleted;
}

bool Board::isFlagged(int index) const {
    return m_flags[index];
}

int Board::getGameElapsedSeconds() const {
    if(m_numUncoveredCells == 0){
        return 0;
    }

    if(
        m_isGameCompleted  ||
        m_isGameOver
    )
    {
        return m_gameStopTime;
    }

    return m_clock.getElapsedTime().asSeconds();
}

