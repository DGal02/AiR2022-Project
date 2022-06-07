#ifndef HEALTH_POTION_H
#define HEALTH_POTION_H

#include "potion.h"

class Health_potion : public Potion
{
public:
    Health_potion(const sf::Texture &texture);
    void animate();
};

#endif // HEALTH_POTION_H
