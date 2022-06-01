#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
class Bullet : public sf::CircleShape
{
private:
    float speed_x;
    float speed_y;
    float scalar_speed;
    sf::FloatRect custom_bounds;
public:
    Bullet(const sf::Vector2i &vectori,const sf::FloatRect &bounds);
    void bullet_move(const sf::Time &elapsed);
    bool check_border();
};


