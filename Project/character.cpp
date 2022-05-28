#include "character.h"

Character::Character(const sf::Texture &text)
{
    setTexture(text);
     on_ground_left=false;
     on_ground_right=false;
     speed_x=500;
     speed_gravitation=200;
     jump_clock=NULL;
     va_gravitation=0;
}
Character::~Character(){
    delete jump_clock;
}
void Character::walk(const sf::Time &elapsed, int x, sf::View &my_view){

    float moveX=elapsed.asSeconds()*x*speed_x;


    if((getGlobalBounds().left+moveX)<0){
        return;
    }
    if((getGlobalBounds().left+moveX+getGlobalBounds().width)> (2000)){

        return;
    }


    my_view.move(moveX,0);

    //std::cout << "left:" << getGlobalBounds().left << " top:" << getGlobalBounds().top << std::endl;
    move(moveX,0);
}
void Character::gravitation(const sf::Time &elapsed,sf::View &view){
    if(on_ground()){
        va_gravitation=0;
    }else{
        va_gravitation+=elapsed.asSeconds()*250;
        float moveY=elapsed.asSeconds()*va_gravitation;
        move(0,moveY);
        view.move(0,moveY);
    }

}
void Character::set_ground_false(){
    on_ground_left=false;
    on_ground_right=false;
}
void Character::check_left(const sf::Sprite &wall, const sf::Time &elapsed){
    float pointX=getGlobalBounds().left;
    float pointY=getGlobalBounds().top+getGlobalBounds().height;
    if(!((wall.getGlobalBounds().top>pointY)&&
         ((pointY+elapsed.asSeconds()*va_gravitation+2)>=wall.getGlobalBounds().top)
         )){
        return;
    }
    if(!(pointX>=wall.getGlobalBounds().left&&pointX<=(wall.getGlobalBounds().left+wall.getGlobalBounds().width))){
        return;
    }
    on_ground_left=true;

}
void Character::check_right(const sf::Sprite &wall,const sf::Time &elapsed){
    float pointX=getGlobalBounds().left+getGlobalBounds().width;
    float pointY=getGlobalBounds().top+getGlobalBounds().height;
    if(!((wall.getGlobalBounds().top>pointY)&&
         ((pointY+elapsed.asSeconds()*va_gravitation+2)>=wall.getGlobalBounds().top)
         )){

        return;
    }
    if(!(pointX>=wall.getGlobalBounds().left&&pointX<=(wall.getGlobalBounds().left+wall.getGlobalBounds().width))){
        return;
    }
    on_ground_right=true;
}
bool Character::on_ground(){
    return (on_ground_left||on_ground_right);
}
void Character::set_jump(){
    if(jump_clock==NULL&&on_ground()){
        jump_clock=new sf::Clock;
    }

}
sf::Clock* Character::r_jump_clock(){
    return jump_clock;
}
void Character::jump(const sf::Time &elapsed,sf::View &view){
    if(jump_clock==NULL){
        return;
    }

    if(jump_clock->getElapsedTime().asSeconds()>=0.5){
        delete jump_clock;
        jump_clock=NULL;
    }
    move(0,-elapsed.asSeconds()*speed_gravitation*3);
    view.move(0,-elapsed.asSeconds()*speed_gravitation*3);
    va_gravitation=0;
}
