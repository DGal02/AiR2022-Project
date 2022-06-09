#pragma once

#include "enemy.h"

class Shoter : public Enemy
{
private:
    sf::Clock bullet_timer;
    std::vector<std::unique_ptr<Bullet>> bullets;
public:
    Shoter(const sf::Texture &texture);
    void draw_bullets(sf::RenderWindow &window);
    void create_bullet(const sf::FloatRect &bounds);
    void bullets_move(const sf::Time &elapsed);
};


