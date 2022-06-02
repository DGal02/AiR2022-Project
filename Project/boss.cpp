#include "boss.h"

Boss::Boss(const sf::Texture &texture)
{

    setScale(0.1,0.1);
    setPosition(500,500);
    setTexture(texture);
    alive=false;
    speed_x=800;
    speed_y=800;
    custom_bounds=sf::FloatRect(0.f,-300.f,2000.f,1100.f);


}
void Boss::boss_move(const sf::Time &elapsed){
    rotate(elapsed.asSeconds()*50);
    bounce();
    move(elapsed.asSeconds()*speed_x,elapsed.asSeconds()*speed_y);
}
void Boss::bounce(){
    sf::FloatRect rectangle_bounds=this->getGlobalBounds();
    // Y axis-right
    if((rectangle_bounds.top+rectangle_bounds.height)>=(custom_bounds.top+custom_bounds.height)){
        speed_y=-std::abs(speed_y);



    }
    // Y axis-left
    if((rectangle_bounds.top)<=custom_bounds.top){
        speed_y=std::abs(speed_y);



    }
    // X axis-right
    if((rectangle_bounds.left+rectangle_bounds.width)>=(custom_bounds.left+custom_bounds.width)){
        speed_x=-std::abs(speed_x);



    }
    // X axis-left
    if((rectangle_bounds.left)<=custom_bounds.left){
        speed_x=std::abs(speed_x);


    }
}
