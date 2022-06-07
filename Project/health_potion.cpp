#include "health_potion.h"

Health_potion::Health_potion(const sf::Texture &texture) :Potion(texture)
{
    setTextureRect(sf::IntRect(frame*50,0,50,64));

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
