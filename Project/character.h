#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Character : public sf::Sprite
{
private:
    int speed_x;
    int speed_y;
    bool on_ground_left;
    bool on_ground_right;
public:
    Character(const sf::Texture &texture);
    Character();
    void walk(const sf::Time &elapsed,int x,sf::View &my_view);
    void gravitation(const sf::Time &elapsed);
};


