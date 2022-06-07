#pragma once
#include <SFML/Graphics.hpp>

class Potion : public sf::Sprite
{
protected:
    sf::Clock clock_animate;
    int frame;
public:
    Potion(const sf::Texture &texture);
    virtual void animate();
};


