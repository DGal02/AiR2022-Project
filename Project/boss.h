#pragma once
#include <SFML/Graphics.hpp>


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
public:
    Boss(const sf::Texture &texture,const sf::Font &font);
    void boss_move (const sf::Time &elapsed);
    void bounce();
    void reduce_hp(int x=1);
    int get_hp();
    sf::Text get_text_hp();

};


