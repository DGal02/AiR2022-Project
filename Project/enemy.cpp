#include "enemy.h"
Enemy::Enemy(const sf::Texture &texture)
{
    setTexture(texture);
    turned_right=false;
    hp=rand()%2 +1;
    rectangle_hp.setSize(sf::Vector2f(0,0));
    first_turn=true;
}
void Enemy::catch_character(const sf::Time &elapsed, const sf::FloatRect &bounds){

    float a=bounds.top-getGlobalBounds().top;
    float b=bounds.left-getGlobalBounds().left;
    float c=sqrt(a*a+b*b);
    if(c==0){
        return;
    }
    float sina=a/c;
    float cosa=b/c;
    if(cosa<0&&!turned_right&&(turn_clock.getElapsedTime().asSeconds()>=0.3||first_turn==true)){
        turn_clock.restart();
        float position_Y=getGlobalBounds().top;
        float position_X=getGlobalBounds().left;
        scale(-1,1);
        turned_right=true;
        setPosition(position_X,position_Y);
        first_turn=false;
    }
    if(cosa>0&&turned_right&&(turn_clock.getElapsedTime().asSeconds()>=0.3||first_turn==true)){
       turn_clock.restart();
       float position_Y=getGlobalBounds().top;
       float position_X=getGlobalBounds().left;
        scale(-1,1);
        turned_right=false;
        setPosition(position_X,position_Y);
        first_turn=false;

    }
    float moveX=elapsed.asSeconds()*scalar_speed*cosa;
    float moveY=elapsed.asSeconds()*scalar_speed*sina;
    move(moveX,moveY);
    set_rectangle_hp();

}
void Enemy::animate(){

}
int Enemy::get_hp(){
    return hp;
}
void Enemy::reduce_life(int x){
    hp-=x;
}
void Enemy::set_rectangle_hp(){
    if(hp<=0){
        return;
    }
    rectangle_hp.setSize(sf::Vector2f(getGlobalBounds().width*hp*(1.f/2.f),10));
    rectangle_hp.setPosition(getGlobalBounds().left, getGlobalBounds().top-rectangle_hp.getGlobalBounds().height);
    if(hp==2){
        rectangle_hp.setFillColor(sf::Color::Green);
    }
    if(hp==1){
        rectangle_hp.setFillColor(sf::Color::Yellow);
    }

}
sf::RectangleShape Enemy::get_rectangle_hp(){
    return rectangle_hp;
}
