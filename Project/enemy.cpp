#include "enemy.h"
Enemy::Enemy(const sf::Texture &texture)
{
    setTexture(texture);
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
    float moveX=elapsed.asSeconds()*scalar_speed*cosa;
    float moveY=elapsed.asSeconds()*scalar_speed*sina;
    move(moveX,moveY);

}
void Enemy::animate(){

}
