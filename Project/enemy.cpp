#include "enemy.h"
Enemy::Enemy(const sf::Texture &texture)
{
    setTexture(texture);
    turned_right=false;
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
    if(cosa<0&&!turned_right&&turn_clock.getElapsedTime().asSeconds()>=0.3){
        turn_clock.restart();
        scale(-1,1);
        turned_right=true;
    }
    if(cosa>0&&turned_right&&turn_clock.getElapsedTime().asSeconds()>=0.3){
       turn_clock.restart();
        scale(-1,1);
        turned_right=false;
    }
    float moveX=elapsed.asSeconds()*scalar_speed*cosa;
    float moveY=elapsed.asSeconds()*scalar_speed*sina;
    move(moveX,moveY);

}
void Enemy::animate(){

}
