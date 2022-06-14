#include "character.h"

Character::Character(const sf::Texture &text)
{
    setTexture(text);
     on_ground_left=true;
     on_ground_right=true;
     speed_x=500;
     speed_gravitation=200; //Wczytanie
     jump_clock=NULL;
     collision_clock=NULL;
     va_gravitation=0;
     hp=5; //Wczytanie
     points=0;
     const_a_gravitation=400;
     killed_boss=false;
     double_shot_clock=NULL;
     enabled_double_shot=false;
     jump_or_die=5.f;
     extra_speed_gravitation=5;
     extra_immortal_time=0.0;
}
Character::~Character(){
    delete jump_clock;
    delete collision_clock;
    delete double_shot_clock;
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
        va_gravitation+=elapsed.asSeconds()*const_a_gravitation;
        float moveY=elapsed.asSeconds()*va_gravitation;
        move(0,moveY);
        view.move(0,moveY);
    }

}
void Character::set_ground_false(){
    on_ground_left=false;
    on_ground_right=false;
}
void Character::check_left(Wall &wall, const sf::Time &elapsed){
    float pointX=getGlobalBounds().left;
    float pointY=getGlobalBounds().top+getGlobalBounds().height;
    if(!((wall.getGlobalBounds().top>pointY)&&
         ((pointY+elapsed.asSeconds()*va_gravitation+5.f)>=wall.getGlobalBounds().top)
         )){
        return;
    }
    if(!(pointX>=wall.getGlobalBounds().left&&pointX<=(wall.getGlobalBounds().left+wall.getGlobalBounds().width))){
        return;
    }
    if(wall.get_to_collect()){
        wall.reset();
        extra_immortal_time+=0.1;

    }
    on_ground_left=true;

}
void Character::check_right(Wall &wall,const sf::Time &elapsed){
    float pointX=getGlobalBounds().left+getGlobalBounds().width;
    float pointY=getGlobalBounds().top+getGlobalBounds().height;
    if(!((wall.getGlobalBounds().top>pointY)&&
         ((pointY+elapsed.asSeconds()*va_gravitation+5.f)>=wall.getGlobalBounds().top)
         )){

        return;
    }
    if(!(pointX>=wall.getGlobalBounds().left&&pointX<=(wall.getGlobalBounds().left+wall.getGlobalBounds().width))){
        return;
    }
    if(wall.get_to_collect()){
        wall.reset();
        extra_immortal_time+=0.1;

    }
    on_ground_right=true;
    std::cout << speed_gravitation << std::endl;
}
bool Character::on_ground(){
    return (on_ground_left||on_ground_right);
}
void Character::set_jump(){
    if(jump_clock==NULL&&on_ground()){
        jump_clock=new sf::Clock;
    }
    if(jump_clock!=NULL&&on_ground()){
        jump_clock->restart();
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
    jump_rectangle_clock.restart();
    move(0,-elapsed.asSeconds()*speed_gravitation*3);
    view.move(0,-elapsed.asSeconds()*speed_gravitation*3);
    va_gravitation=0;
}
void Character::reduce_life(sf::Sound &sound,int x){
    hp-=x;
    sound.play();
}
int Character::get_hp(){
    return hp;
}
bool Character::przegrana(){
    if(hp<=0){
        return true;
    }
    return false;
}
bool Character::wygrana(){
    if(points>=20&&killed_boss){
        return true;
    }
    return false;
}
void Character::add_points(int x){
    points+=x;
}
void Character::collision(sf::Sound &sound){
    if(!(collision_clock==NULL)){
        if(collision_clock->getElapsedTime().asSeconds()>=3.0+extra_immortal_time){

            collision_clock->restart();
            delete collision_clock;
            collision_clock=NULL;
        }
    }
    if(collision_clock==NULL){
       hp--;
       sound.play();
       collision_clock=new sf::Clock;

    }
}
int Character::get_points(){
    return points;
}
bool Character::immortal(){
    if(collision_clock==NULL){
        return false;
    } else {
        if(collision_clock->getElapsedTime().asSeconds()<=3.0 +extra_immortal_time){
            return true;
        }
        return false;
    }

}
void Character::kill_boss(){
    killed_boss=true;
}
bool Character::get_killed_boss(){
    return killed_boss;
}
void Character::add_hp(int x){
    hp+=x;
}
void Character::set_mouse_position(const sf::Vector2i &pos,const sf::FloatRect &bounds){
    if(double_shot_clock!=NULL){
        return;
    }
    double_shot_clock=new sf::Clock;
    mouse_position=pos;
    bounds_double_shot=bounds;
}
bool Character::get_if_double_shot(){
    if(double_shot_clock==NULL){
        return false;
    }
    if(double_shot_clock->getElapsedTime().asSeconds()>=0.1){
        delete double_shot_clock;
        double_shot_clock=NULL;
        return true;
    }
    return false;
}
sf::Vector2i Character::get_mouse_position(){
    return mouse_position;
}
sf::FloatRect Character::get_bounds_double_shot(){
    return bounds_double_shot;
}
bool Character::get_enabled_double_shot(){
    return enabled_double_shot;
}
void Character::enable_double_shot(){
    enabled_double_shot=true;
}
void Character::set_rectangle_jump(sf::Sound &sound){
    jump_rectangle.setSize(sf::Vector2f(40.f*jump_rectangle_clock.getElapsedTime().asSeconds(),20.f));
    if(jump_rectangle_clock.getElapsedTime().asSeconds()>jump_or_die){
        reduce_life(sound,hp);
    }
    if(jump_rectangle_clock.getElapsedTime().asSeconds()>jump_or_die-(1.f/3.f)*jump_or_die){
        jump_rectangle.setFillColor(sf::Color::Red);
        return;
    }
    if(jump_rectangle_clock.getElapsedTime().asSeconds()>jump_or_die-(2.f/3.f)*jump_or_die){
        jump_rectangle.setFillColor(sf::Color::Yellow);
        return;
    }
    if(jump_rectangle_clock.getElapsedTime().asSeconds()>jump_or_die-(3.f/3.f)*jump_or_die){
        jump_rectangle.setFillColor(sf::Color::Green);
        return;
    }

}
sf::RectangleShape Character::get_rectangle_jump(){
    return jump_rectangle;
}
