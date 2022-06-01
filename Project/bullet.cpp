#include "bullet.h"

Bullet::Bullet(const sf::Vector2i &vectori,const sf::FloatRect &bounds)
{
    custom_bounds=sf::FloatRect(0.f,-300.f,2000.f,1100.f);
    setPosition(bounds.left,bounds.top);
    setFillColor(sf::Color::Red);
    setRadius(20);

    scalar_speed=800;
   // float a=bounds.top-getGlobalBounds().top;
    float a=-(bounds.top+bounds.height/2 -vectori.y);
   // float b=bounds.left-getGlobalBounds().left;
    float b=-(bounds.left+bounds.width/2-vectori.x);
    float c=sqrt(a*a+b*b);
    if(c==0){
        return;
    }
    float sina=a/c;
    float cosa=b/c;

     speed_x=scalar_speed*cosa;
     speed_y=scalar_speed*sina;
}
void Bullet::bullet_move(const sf::Time &elapsed){
    move(speed_x*elapsed.asSeconds(),speed_y*elapsed.asSeconds());



}
bool Bullet::check_border(){
    sf::FloatRect rectangle_bounds=this->getGlobalBounds();
    // Y axis-right
    if((rectangle_bounds.top+rectangle_bounds.height)>=(custom_bounds.top+custom_bounds.height)){
        return true;



    }
    // Y axis-left
    if((rectangle_bounds.top)<=custom_bounds.top){
        return true;



    }
    // X axis-right
    if((rectangle_bounds.left+rectangle_bounds.width)>=(custom_bounds.left+custom_bounds.width)){
        return true;



    }
    // X axis-left
    if((rectangle_bounds.left)<=custom_bounds.left){
        return true;


    }
    return false;
}
