//
// File: main.cpp
// Description: main file for the Minimal Minesweeper game.
//

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <vector>
#include <stdlib.h>
#include <iostream>

#include "config.h"
#include "config_internal.h"
#include "board.h"
#include "sprite_manager.h"

using namespace std;

void processLeftMouseEvent(int window_x, int window_y, Board* board){
    int x = (window_x-CELL_SPACING) / (CELL_WIDTH+CELL_SPACING);
    int y = (window_y-CELL_SPACING) / (CELL_HEIGHT+CELL_SPACING);

    // if click is in the grid region
    if(y<NUM_ROWS){
        board->uncoverCell(x, y);
        board->calculateGameCompleted();
    }
    // if click is in the emoji region
    else if((window_x >= emojiPosition_x) &&
       (window_x <= emojiPosition_x+CELL_WIDTH)){
        board->resetBoard();
    }

}

void processRightMouseEvent(int window_x, int window_y, Board* board){
    // windows coordinates to grid coordinates
    int x = (window_x-CELL_SPACING) / (CELL_WIDTH+CELL_SPACING);
    int y = (window_y-CELL_SPACING) / (CELL_HEIGHT+CELL_SPACING);

    board->flagCell(x, y);
}

void processDoubleButton(int window_x, int window_y, Board* board){
    int x = (window_x-CELL_SPACING) / (CELL_WIDTH+CELL_SPACING);
    int y = (window_y-CELL_SPACING) / (CELL_HEIGHT+CELL_SPACING);
    int index = board->indexFromCellCoords(x, y);
    vector<sf::Vector2u> neighbors = board->getNeighbors(x, y);

    int flaggedNeighbors = board->getNumberOfFlaggedNeighbors(x, y);
    int neighborMines = board->countNeighborMines(x, y);

    // cells propagation
    if(
        board->isUncovered(index)           &&  // cell is already uncovered
        (flaggedNeighbors == neighborMines)
    )
    {
        for(auto neighbor: neighbors){
            board->uncoverCell(neighbor.x, neighbor.y);
        }
    }


}

int main() {

    Board* board = new Board();
    SpriteManager* spriteManager = new SpriteManager();

    // Calculate window dimensions
    int window_width  = CELL_SPACING + (NUM_COLS * (CELL_WIDTH +CELL_SPACING));
    int window_height = CELL_SPACING + (NUM_ROWS * (CELL_HEIGHT+CELL_SPACING))
                      + (CELL_HEIGHT+CELL_SPACING);

    // create the window
    sf::RenderWindow window(sf::VideoMode(window_width, window_height), "Minimal Minesweeper");
    window.setFramerateLimit(GAME_FRAMERATE);


    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed){
                window.close();
            }

            // Process mouse events
            if (event.type == sf::Event::MouseButtonPressed)
            {
                bool right = sf::Mouse::isButtonPressed(sf::Mouse::Right);
                bool left  = sf::Mouse::isButtonPressed(sf::Mouse::Left);
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    if((left == true) && (right == true)){
                        processDoubleButton(event.mouseButton.x, event.mouseButton.y, board);
                    }
                    else{
                        processLeftMouseEvent(event.mouseButton.x, event.mouseButton.y, board);
                    }
                }
                if (event.mouseButton.button == sf::Mouse::Right)
                {
                    if((left == true) && (right == true)){
                        processDoubleButton(event.mouseButton.x, event.mouseButton.y, board);
                    }
                    else{
                        processRightMouseEvent(event.mouseButton.x, event.mouseButton.y, board);
                    }
                }
            }

            if (event.type == sf::Event::KeyPressed){
                if (event.key.code == sf::Keyboard::Space)
                {
                    board->resetBoard();
                }
            }
        }

        spriteManager->draw(window, board);

        // end the current frame
        window.display();
    }
}

