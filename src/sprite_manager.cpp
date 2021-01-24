#include <iostream>
#include "sprite_manager.h"
#include "config_internal.h"
#include "board.h"

using namespace std;

SpriteManager::SpriteManager(){
    init();
}

void SpriteManager::loadTextures(){
    // Generate loading for all textures
    #define SPRITE_DEF(spriteName, textureName, spritePath)     \
        if(!textureName.loadFromFile(spritePath)){              \
        cout << "Error loading texture " << spritePath << endl; \
    }
    #include "sprite_config.h"
}

void SpriteManager::initSprites(){
    // Generate the texture setting for each sprite
    #define SPRITE_DEF(spriteName, textureName, spritePath) \
        spriteName.setTexture(textureName);
    #include "sprite_config.h"
}

void SpriteManager::init(){
    rectangle.setSize(CELL_SIZE);
    rectangle.setFillColor(CELL_COLOR);
    clr_rectangle.setSize(CELL_SIZE);
    clr_rectangle.setFillColor(COLOR_CLR_RCTNGL);

    sprt_dead.setPosition(emojiPosition_x, emojiPosition_y);
    sprt_hppy.setPosition(emojiPosition_x, emojiPosition_y);
    sprt_done.setPosition(emojiPosition_x, emojiPosition_y);

    loadTextures();
    initSprites();
}

void SpriteManager::draw(sf::RenderWindow& window, Board* board){
    window.clear(BGRND_COLOR);

    // draw elements on the grid
    for(int y=0; y<NUM_ROWS; y++){
    for(int x=0; x<NUM_COLS; x++){
        int numNeighborMines = board->countNeighborMines(x, y);
        int index = NUM_COLS*y + x;
        // position coordinates where the next sprite will be drawn
        int window_x = CELL_SPACING                 // initial offset
                       + (CELL_SPACING+CELL_WIDTH)  // + cell width and spacing
                       * x;                         // current cell coord
        int window_y = CELL_SPACING
                       + (CELL_SPACING+CELL_HEIGHT)
                       * y;

        // Draw normal square
        sf::Vector2f square_pos(window_x, window_y);
        sprt_ucvd.setPosition(square_pos);
        window.draw(sprt_ucvd);

        // draw a light silver square
        if(
            (numNeighborMines==0)       &&  // cell has no neighbor mines
            (board->isUncovered(index))     // cell has been uncovered
        )
        {
            sprt_clrd.setPosition(square_pos);
            window.draw(sprt_clrd);
        }

        // Draw mine
        if(
            board->isMine(index)        &&
            board->isUncovered(index)
        )
        {
            sprt_bomb.setPosition(window_x, window_y);
            window.draw(sprt_bomb);
        }

        // Draw remaining uncovered mines
        if(
            (
                board->isGameCompleted()    ||
                board->isGameOver()             // game is completed or over
            )
            &&
            board->isMine(index)        &&  // cell has no mine
            !board->isFlagged(index)       // cell is not flagged
        )
        {
            sprt_bomb.setPosition(window_x, window_y);
            window.draw(sprt_bomb);
        }

        // Draw the number of neighbor cells
        if(
            !board->isMine(index)       &&  // cell does not contain a mine
            (numNeighborMines > 0)      &&  // cell has 1+ neighbors
            board->isUncovered(index)       // cell has been uncovered
        )
        {
            sf::Sprite* numberSprite = sprites[numNeighborMines];
            numberSprite->setPosition(window_x, window_y);
            window.draw(*numberSprite);
        }

        // Draw flag
        if(board->isFlagged(index)){
            sprt_flag.setPosition(window_x, window_y);
            window.draw(sprt_flag);
        }

        // Draw the emoji face
        if(board->isGameCompleted()){
            window.draw(sprt_done);
        }
        else if(board->isGameOver()){
            window.draw(sprt_dead);
        }
        else{
            window.draw(sprt_hppy);
        }



    }
    }

    // draw elapsed time
    int elapsedSeconds = board->getGameElapsedSeconds();
    // draw the ones
    sf::Sprite* timSprite = timSprites[elapsedSeconds%10];
    timSprite->setPosition(TIMER_ONES_POS_X,TIMER_ONES_POS_Y);
    window.draw(*timSprite);
    // draw the tens
    elapsedSeconds /= 10;
    timSprite = timSprites[elapsedSeconds%10];
    timSprite->setPosition(TIMER_TENS_POS_X,TIMER_TENS_POS_Y);
    window.draw(*timSprite);
    // draw the hundreds
    elapsedSeconds /= 10;
    timSprite = timSprites[elapsedSeconds%10];
    timSprite->setPosition(TIMER_HUNS_POS_X,TIMER_HUNS_POS_Y);
    window.draw(*timSprite);
}

// EOF
