//
// File: sprite_manager.h
// Description: The sprite manager loads sprites and draws to the screen.
//

#include <SFML/Graphics.hpp>
#include <vector>

class Board;

class SpriteManager{
    // generate texture and sprite declarations
    #define SPRITE_DEF(spriteName, textureName, spritePath) \
        sf::Texture textureName;                            \
        sf::Sprite  spriteName;
    #include "sprite_config.h"
    sf::RectangleShape rectangle;
    sf::RectangleShape clr_rectangle;
    std::vector<sf::Sprite*>
    sprites{
        &sprt_bomb,
        &sprt_num1,
        &sprt_num2,
        &sprt_num3,
        &sprt_num4,
        &sprt_num5,
        &sprt_num6,
        &sprt_num7,
        &sprt_num8,
    };
    std::vector<sf::Sprite*>
    timSprites{
        &sprt_tim0,
        &sprt_tim1,
        &sprt_tim2,
        &sprt_tim3,
        &sprt_tim4,
        &sprt_tim5,
        &sprt_tim6,
        &sprt_tim7,
        &sprt_tim8,
        &sprt_tim9
    };

public:
    SpriteManager();
    void loadTextures();
    void initSprites();
    void init();
    void draw(sf::RenderWindow& window, Board* board);
};
