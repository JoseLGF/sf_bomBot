//
// File: config_internal.h
// Description: This file contains constant definitions that are used by the
//      software, based on previous user configurations.
//      This file should not be changed by the user.
//

#ifndef CONFIG_INTERNAL_H
#define CONFIG_INTERNAL_H

#include "config.h"

const sf::Vector2f  CELL_SIZE       = sf::Vector2f(CELL_WIDTH, CELL_HEIGHT);
const int           TOTAL_CELLS     = NUM_ROWS * NUM_COLS;

const int emojiPosition_x = ((CELL_WIDTH+CELL_SPACING)*(NUM_COLS/2.0)) - ((CELL_WIDTH+CELL_SPACING)/2.0) + CELL_SPACING;
const int emojiPosition_y = (CELL_HEIGHT+CELL_SPACING)*(NUM_ROWS);

const int  TIMER_ONES_POS_X = CELL_SPACING + (CELL_WIDTH+CELL_SPACING)*2;
const int  TIMER_ONES_POS_Y = (CELL_HEIGHT+CELL_SPACING)*(NUM_ROWS);
const int  TIMER_TENS_POS_X = CELL_SPACING + (CELL_WIDTH+CELL_SPACING)*1;
const int  TIMER_TENS_POS_Y = (CELL_HEIGHT+CELL_SPACING)*(NUM_ROWS);
const int  TIMER_HUNS_POS_X = CELL_SPACING + (CELL_WIDTH+CELL_SPACING)*0;
const int  TIMER_HUNS_POS_Y = (CELL_HEIGHT+CELL_SPACING)*(NUM_ROWS);

#endif // CONFIG_INTERNAL_H
