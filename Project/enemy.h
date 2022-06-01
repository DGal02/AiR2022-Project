#pragma once
#include <cmath>
#include <SFML/Graphics.hpp>
class Enemy : public sf::Sprite
{
protected:
    int speed_x;
    int speed_y;
    int scalar_speed;
    bool turned_right;
    sf::Clock turn_clock;
public:
    Enemy(const sf::Texture &texture);
    virtual void catch_character(const sf::Time &elapsed, const sf::FloatRect &bounds);
    virtual void animate();
};


