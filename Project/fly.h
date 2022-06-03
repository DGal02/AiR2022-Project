#pragma once

#include "enemy.h"

class Fly : public Enemy
{
private:
    int frame;
    sf::Clock timer_animation;
public:
    Fly(const sf::Texture &texture);
    void animate();
};


