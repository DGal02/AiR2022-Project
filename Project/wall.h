#pragma once
#include <SFML/Graphics.hpp>


class Wall : public sf::Sprite
{
private:
    sf::RectangleShape outline;
    bool to_collect;
public:
    Wall();
    bool get_to_collect();
    void set_to_collect();
    void reset();
    sf::RectangleShape get_outline();
};


