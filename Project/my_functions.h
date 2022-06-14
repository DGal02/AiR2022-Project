#pragma once
#include <iostream>
#include <math.h>
#include <algorithm>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "character.h"
#include "wall.h"
#include "fire.h"
#include "enemy.h"
#include "fly.h"
#include "bullet.h"
#include "boss.h"
#include "ghost.h"
#include "potion.h"
#include "health_potion.h"
#include "double_shot_potion.h"
#include "shoter.h"

void main_game();
void title_screen();
template <class name>
void new_enemy(std::vector<std::unique_ptr<Enemy>> &enemies,const sf::Texture &texture,float x,float y);
void Create_wall(std::vector<Wall> &walls, const sf::Texture &texture,int x,int y);
void Create_mob_resp(std::vector<sf::Sprite> &mob_resp,const sf::Texture &texture);
void Wygrana(sf::RenderWindow &window,sf::Text &text);
void Przegrana(sf::RenderWindow &window,sf::Text &text,sf::Sound &sound);
void CheckView(sf::RenderWindow &window,sf::View &view,const Fire &fire);
template <class name>
void new_enemy(std::vector<std::unique_ptr<Enemy>> &enemies,const sf::Texture &texture,float x,float y);
float get_left_view(const sf::RenderWindow &window);
float get_top_view(const sf::RenderWindow &window);
void main_game();
void mouse_move(const sf::Time &elapsed,float x=0,float y=0);
void set_wall_to_obtain(const Character &character, std::vector<Wall> &walls);
