#include "fire.h"

Fire::Fire(sf::Texture frame0,sf::Texture frame1,sf::Texture frame2,sf::Texture frame3){
    frames.emplace_back(frame0);
    frames.emplace_back(frame1);
    frames.emplace_back(frame2);
    frames.emplace_back(frame3);
    setTexture(frames[0]);
    current_frame=0;

}
void Fire::animate(){
    if(clock.getElapsedTime().asSeconds()<0.1f){
        return;
    }
    clock.restart();
    if(current_frame>=3){
        current_frame=0;
    } else{
        current_frame++;
    }
    setTexture(frames[current_frame]);
}
