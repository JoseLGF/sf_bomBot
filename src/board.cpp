#include "config.h"
#include "board.h"

using namespace std;

int Board::indexFromCellCoords(int x, int y){
    return ((y*NUM_COLS) + x);
}

vector<sf::Vector2u> Board::getNeighbors(int x, int y){
    vector<sf::Vector2u> out;
    for(int i=x-1; i<=x+1; i++){
    for(int j=y+1; j>=y-1; j--){
        if(
            (i < 0)            ||
            (i > (NUM_COLS-1)) ||
            (j < 0)            ||
            (j > (NUM_ROWS-1)) ||
            ((i==x) && (j==y))
        )
        {
            continue;
        }
        out.push_back(sf::Vector2u(i, j));
    }
    }
    return out;
}

int Board::countNeighborMines(int x, int y){
    int counter = 0;
    vector<sf::Vector2u> neighbors = getNeighbors(x, y);
    for(auto neighbor: neighbors){
        if(mines[indexFromCellCoords(neighbor.x, neighbor.y)]){
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
        uncovered[index]        || // Cell has been previously uncovered
        flags[index]            || // Cell has been flagged
        (index >= TOTAL_CELLS)         // index exceeds grid dimensions
    )
    {
        return;
    }

    // Avoids making the player lose on their first move.
    // Also detect player first move to start time count
    if(numUncoveredCells == 0){
        clock.restart();
        mines[index] = false;
    }

    // Uncover this cell
    uncovered[index] = true;
    numUncoveredCells++;
    calculateGameCompleted();

    // If uncovered cell contains a mine, game over
    if(mines[index]){
        m_isGameOver = true;
        gameStopTime = clock.getElapsedTime().asSeconds();
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

void Board::calculateGameCompleted(){
    int numOfNonMines = count(mines.begin(), mines.end(), false);
    if((numUncoveredCells == numOfNonMines) && !m_isGameOver){
        // winning time is captured only once
        if(!m_isGameCompleted){gameStopTime = clock.getElapsedTime().asSeconds();}
        m_isGameCompleted = true;
    }
}

void Board::resetBoard(){
    // variables are (void)'ed in order to prevent compiler's unused warning
    for(auto& mine: mines)     { mine = false; (void)mine;}
    for(auto& flag: flags)     { flag = false; (void)flag;}
    for(auto& cell: uncovered) { cell = false; (void)cell;}

    // Initialize mines
    srand (time(NULL));
    //srand(1);
    for(auto& mine: mines){
        mine = !(rand() % GAME_CELLTOMINERATIO);
        (void)mine;
    }

    numUncoveredCells   = 0;
    m_isGameOver          = false;
    m_isGameCompleted     = false;
}

void Board::flagCell(int x, int y){
    int index = NUM_COLS*y + x;
    // don't flag this cell if...
    if(
        m_isGameOver            ||
        m_isGameCompleted       ||
        index >= TOTAL_CELLS    || // index exceeds grid dimensions
        uncovered[index]           // cell has already been uncovered
    )
    {
        return;
    }

    flags[index] = !flags[index];

}

int Board::getNumberOfFlaggedNeighbors(int x, int y){
    int flaggedNeighbors = 0;
    vector<sf::Vector2u> neighbors = getNeighbors(x, y);
    for(auto neighbor: neighbors){
        int neighborIndex = indexFromCellCoords(neighbor.x, neighbor.y);
        if(flags[neighborIndex]){
            flaggedNeighbors++;
        }
    }

    return flaggedNeighbors;
}

Board::Board(){
    resetBoard();
}

bool Board::isUncovered(int index){
    return uncovered[index];
}

bool Board::isMine(int index){
    return mines[index];
}

bool Board::isGameOver(){ return m_isGameOver;}
bool Board::isGameCompleted(){ return m_isGameCompleted;}


bool Board::isFlagged(int index){
    return flags[index];
}

int Board::getGameElapsedSeconds(){
    if(numUncoveredCells == 0){
        return 0;
    }
    if(
        m_isGameCompleted  ||
        m_isGameOver
    )
    {
        return gameStopTime;
    }

    return clock.getElapsedTime().asSeconds();
}

