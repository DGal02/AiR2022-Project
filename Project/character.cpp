#include "character.h"

Character::Character(const sf::Texture &text)
{
    setTexture(text);
     on_ground_left=false;
     on_ground_right=false;
}
void Character::walk(const sf::Time &elapsed, int x, sf::View &my_view){

    float moveX=elapsed.asSeconds()*x*500;


    if((getGlobalBounds().left+moveX)<0){
        return;
    }
    if((getGlobalBounds().left+moveX+getGlobalBounds().width)> (2000)){

        return;
    }


    my_view.move(moveX,0);

    std::cout << "left:" << getGlobalBounds().left << " top:" << getGlobalBounds().top << std::endl;
    move(moveX,0);
}
void Character::gravitation(const sf::Time &elapsed){
    move(0,elapsed.asSeconds()*100);
}
