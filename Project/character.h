#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <SFML/Audio.hpp>
#include "wall.h"
class Character : public sf::Sprite
{
private:
    int speed_x;
    int speed_gravitation;
    int extra_speed_gravitation;
    float extra_immortal_time;
    int hp;
    int points;
    int const_a_gravitation;
    float jump_or_die;
    bool on_ground_left;
    bool on_ground_right;
    bool enabled_double_shot;
    sf::Clock* jump_clock;
    sf::Clock* collision_clock;
    sf::Clock* double_shot_clock;
    float va_gravitation;
    bool killed_boss;
    sf::Vector2i mouse_position;
    sf::FloatRect bounds_double_shot;
    sf::RectangleShape jump_rectangle;
    sf::Clock jump_rectangle_clock;
    sf::Clock teleport_clock;

public:
    Character(const sf::Texture &texture);
    Character();
    virtual ~Character();
    void walk(const sf::Time &elapsed,int x,sf::View &my_view);
    void gravitation(const sf::Time &elapsed, sf::View &view);
    void set_ground_false();
    void check_left(Wall &wall,const sf::Time &elapsed);
    void check_right(Wall &wall,const sf::Time &elapsed);
    void set_jump();
    void jump(const sf::Time &elapsed, sf::View &view);
    void reduce_life(sf::Sound &sound,int x=1);
    void add_points(int x=1);
    void collision(sf::Sound &sound);
    void kill_boss();
    void add_hp(int x=1);
    void set_mouse_position(const sf::Vector2i &pos,const sf::FloatRect &bounds);
    void enable_double_shot();
    void set_rectangle_jump(sf::Sound &sound);
    void teleport(sf::View &view);
    sf::Clock* r_jump_clock();
    int get_hp(); 
    int get_points();
    sf::Vector2i get_mouse_position();
    sf::FloatRect get_bounds_double_shot();
    sf::RectangleShape get_rectangle_jump();
    bool on_ground();
    bool przegrana();
    bool wygrana();
    bool immortal();
    bool get_killed_boss();
    bool get_if_double_shot();
    bool get_enabled_double_shot();
};


