#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Character : public sf::Sprite
{
private:
    int speed_x;
    int speed_gravitation;
    bool on_ground_left;
    bool on_ground_right;
    sf::Clock* jump_clock;
    float va_gravitation;
    int hp;
    int points;

public:
    Character(const sf::Texture &texture);
    Character();
    ~Character();
    void walk(const sf::Time &elapsed,int x,sf::View &my_view);
    void gravitation(const sf::Time &elapsed, sf::View &view);
    void set_ground_false();
    void check_left(const sf::Sprite &wall,const sf::Time &elapsed);
    void check_right(const sf::Sprite &wall,const sf::Time &elapsed);
    void set_jump();
    void jump(const sf::Time &elapsed, sf::View &view);
    void reduce_life(int x=1);
    sf::Clock* r_jump_clock();
    int get_hp();
    bool on_ground();
};


