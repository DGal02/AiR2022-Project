#include "fly.h"

Fly::Fly(const sf::Texture &texture) :Enemy(texture)
{
    frame=0;
    setTextureRect(sf::IntRect(32*frame, 0, 32, 32));

    scalar_speed=100;
}
void Fly::animate(){
    if(timer_animation.getElapsedTime().asSeconds()<=0.1f){
        return;
    }
    timer_animation.restart();
    if(frame>=15){
        frame=0;
    } else {
        frame++;
    }
    setTextureRect(sf::IntRect(32*frame, 0, 32, 32));

}
