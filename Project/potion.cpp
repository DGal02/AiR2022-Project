#include "potion.h"

Potion::Potion(const sf::Texture &texture)
{
    setTexture(texture);
    frame=0;
    int positionY=800+1-getGlobalBounds().height;
    int positionX=2000+1-getGlobalBounds().width;
    setPosition(rand()%(positionX),-300+rand()%(positionY-500)+300);

}
void Potion::animate(){

}
