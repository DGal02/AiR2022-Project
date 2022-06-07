#pragma once
#include <SFML/Graphics.hpp>
#include "bullet.h"

class Boss :public sf::Sprite
{
private:
    int hp;
    bool alive;
    int speed_x;
    int speed_y;
    sf::FloatRect custom_bounds;
    sf::Text text_hp;
    void set_hp_text();
    std::vector<std::unique_ptr<Bullet>> bullets;
    void create_bullet(int x,int y);
    sf::Clock clock_bullets;
    void bullets_move(const sf::Time &elapsed);
public:
    Boss(const sf::Texture &texture,const sf::Font &font);
    void boss_move (const sf::Time &elapsed);
    void bounce();
    void reduce_hp(int x=1);
    void shoot_bullets();
    void draw_bullets(sf::RenderWindow &window);
    int get_hp();
    sf::Text get_text_hp();

};


