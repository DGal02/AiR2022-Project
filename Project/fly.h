#ifndef FLY_H
#define FLY_H

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

#endif // FLY_H
