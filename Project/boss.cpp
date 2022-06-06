#include "boss.h"

Boss::Boss(const sf::Texture &texture,const sf::Font &font)
{

    setScale(0.1,0.1);
    custom_bounds=sf::FloatRect(0.f,-300.f,2000.f,1100.f);
    int positionX=custom_bounds.width-getGlobalBounds().width +1;
    int positionY=custom_bounds.height-getGlobalBounds().height+1;
    setPosition(custom_bounds.left+rand()%positionX,custom_bounds.top+rand()%positionY);
    setTexture(texture);
    alive=false;
    speed_x=800;
    speed_y=800;

    hp=20;
    text_hp.setFont(font);
    text_hp.setCharacterSize(40);
    text_hp.setFillColor(sf::Color::White);


}
void Boss::boss_move(const sf::Time &elapsed){
    rotate(elapsed.asSeconds()*50);
    bounce();
    move(elapsed.asSeconds()*speed_x,elapsed.asSeconds()*speed_y);
    set_hp_text();
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
void Boss::reduce_hp(int x){
    hp-=x;
}
int Boss::get_hp(){
    return hp;
}
void Boss::set_hp_text(){
    text_hp.setString("HP: "+std::to_string(hp));
    text_hp.setPosition( getGlobalBounds().left,getGlobalBounds().top-2-text_hp.getGlobalBounds().height );

}
sf::Text Boss::get_text_hp(){
    return text_hp;
}
