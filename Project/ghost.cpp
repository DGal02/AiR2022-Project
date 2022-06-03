#include "ghost.h"

Ghost::Ghost(const sf::Texture &texture): Enemy(texture)
{
scalar_speed=100;
}
void Ghost::animate(){
    if(rand()%100+1==1){
        scalar_speed*=1.25;
    }
}
