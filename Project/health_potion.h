#pragma once

#include "potion.h"

class Health_potion : public Potion
{
public:
    Health_potion(const sf::Texture &texture);
    void animate();
};


