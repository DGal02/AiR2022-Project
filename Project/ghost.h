#pragma once

#include "enemy.h"

class Ghost : public Enemy
{
public:
    Ghost(const sf::Texture &texture);
    void animate();
};


