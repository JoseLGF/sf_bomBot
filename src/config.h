//
// File: config.h
// Description: This file contains configurations that a user
//      can change, such as colors for objects, number of mines, etc.
//      After making changes, it is necessary to recompile the program.
//

#ifndef CONFIG_H
#define CONFIG_H

#include <SFML/Graphics.hpp>
//
// Base Color configurations
//
const sf::Color COLOR_GREY      = sf::Color(150, 150, 150);
const sf::Color COLOR_RED       = sf::Color(250,   0,   0);
const sf::Color COLOR_BLACK     = sf::Color( 30,  30,  30);
const sf::Color COLOR_SILVER    = sf::Color( 70,  70,  70);
const sf::Color COLOR_LGHT_SLVR = sf::Color(230, 230, 230);
const sf::Color COLOR_LGT_BLUE  = sf::Color(100, 100, 255);
const sf::Color COLOR_BLUE      = sf::Color( 50,  50, 255);

//
// Objects' color configurations
//
const sf::Color CELL_COLOR          = COLOR_GREY;
const sf::Color FLAG_COLOR          = COLOR_RED;
const sf::Color BOMB_COLOR          = COLOR_BLACK;
const sf::Color BGRND_COLOR         = COLOR_BLACK;
const sf::Color COLOR_CLR_RCTNGL    = COLOR_SILVER;

//
// Sizes and dimensions
//
const float CELL_WIDTH      = 30.0f;
const float CELL_HEIGHT     = 30.0f;
const float CELL_SPACING    = 5.0f;
const int   CELL_RADIUS     = 15;
const int   BOMB_RADIUS     = 15;
const int   NUM_ROWS        = 15;
const int   NUM_COLS        = 15;


//
// Game Performance
//
const int GAME_FRAMERATE        = 60;
const int GAME_CELLTOMINERATIO  = 10;



#endif // CONFIG_H
