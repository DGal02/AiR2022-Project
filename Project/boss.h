#pragma once
#include <SFML/Graphics.hpp>


class Boss :public sf::Sprite
{
private:
    int hp;
    bool alive;
    int speed_x;
    int speed_y;
    sf::FloatRect custom_bounds;
public:
    Boss(const sf::Texture &texture);
    void boss_move (const sf::Time &elapsed);
    void bounce();
};


