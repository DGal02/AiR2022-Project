#include "health_potion.h"

Health_potion::Health_potion(const sf::Texture &texture) :Potion(texture)
{
    setTextureRect(sf::IntRect(frame*50,0,50,64));
    int positionY=800+1-getGlobalBounds().height;
    int positionX=2000+1-getGlobalBounds().width;
    setPosition(rand()%(positionX),-300+rand()%(positionY-500)+300);
}
void Health_potion::animate(){
    if(clock_animate.getElapsedTime().asSeconds()<=0.1){
        return;
    }
    clock_animate.restart();
    if(frame>=6){
        frame=0;
    } else {
        frame++;
    }
    setTextureRect(sf::IntRect(frame*50,0,50,64));

}
