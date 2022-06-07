#include "boss.h"
Boss::Boss(const sf::Texture &texture,const sf::Font &font)
{

    setScale(0.1,0.1);
    custom_bounds=sf::FloatRect(0.f,-300.f,2000.f,1100.f);
    setPosition(rand()%1800,custom_bounds.top+rand()%900);
    setTexture(texture);
    alive=false;
    speed_x=600;
    speed_y=600;

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
    shoot_bullets();
    bullets_move(elapsed);

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
void Boss::shoot_bullets(){
    if(clock_bullets.getElapsedTime().asSeconds()<=5){
        return;
    }
    clock_bullets.restart();




        create_bullet(300.f+getGlobalBounds().width/2.f,0);
        create_bullet(-300.f-getGlobalBounds().width/2.f,0);
        create_bullet(0.f,300.f+getGlobalBounds().height/2.f);
        create_bullet(0.f,-300.f-getGlobalBounds().height/2.f);



        create_bullet(300.f+getGlobalBounds().width/2.f,300.f+getGlobalBounds().height/2.f);
        create_bullet(-300.f-getGlobalBounds().width/2.f,300.f+getGlobalBounds().height/2.f);
        create_bullet(300.f+getGlobalBounds().width/2.f,-300.f-getGlobalBounds().height/2.f);
        create_bullet(-300.f-getGlobalBounds().width/2.f,-300.f-getGlobalBounds().height/2.f);

        create_bullet(300.f+getGlobalBounds().width/2.f,200.f+getGlobalBounds().height/2.f);
        create_bullet(300.f+getGlobalBounds().width/2.f,100.f+getGlobalBounds().height/2.f);
        create_bullet(200.f+getGlobalBounds().width/2.f,300.f+getGlobalBounds().height/2.f);
        create_bullet(100.f+getGlobalBounds().width/2.f,300.f+getGlobalBounds().height/2.f);

        create_bullet(-300.f-getGlobalBounds().width/2.f,200.f+getGlobalBounds().height/2.f);
        create_bullet(-300.f-getGlobalBounds().width/2.f,100.f+getGlobalBounds().height/2.f);
        create_bullet(-200.f-getGlobalBounds().width/2.f,300.f+getGlobalBounds().height/2.f);
        create_bullet(-100.f-getGlobalBounds().width/2.f,300.f+getGlobalBounds().height/2.f);

        create_bullet(300.f+getGlobalBounds().width/2.f,-200.f-getGlobalBounds().height/2.f);
        create_bullet(300.f+getGlobalBounds().width/2.f,-100.f-getGlobalBounds().height/2.f);
        create_bullet(200.f+getGlobalBounds().width/2.f,-300.f-getGlobalBounds().height/2.f);
        create_bullet(100.f+getGlobalBounds().width/2.f,-300.f-getGlobalBounds().height/2.f);

        create_bullet(-300.f-getGlobalBounds().width/2.f,-200.f-getGlobalBounds().height/2.f);
        create_bullet(-300.f-getGlobalBounds().width/2.f,-100.f-getGlobalBounds().height/2.f);
        create_bullet(-200.f-getGlobalBounds().width/2.f,-300.f-getGlobalBounds().height/2.f);
        create_bullet(-100.f-getGlobalBounds().width/2.f,-300.f-getGlobalBounds().height/2.f);

}
void Boss::create_bullet(int x, int y){
    std::unique_ptr<Bullet> temp_bullet=std::make_unique<Bullet>(sf::Vector2i(getGlobalBounds().left-x,getGlobalBounds().top-y),getGlobalBounds());
    temp_bullet->setRadius(15);
    temp_bullet->setFillColor(sf::Color::Yellow);

    bullets.emplace_back(std::move(temp_bullet));
}
void Boss::draw_bullets(sf::RenderWindow &window){
    for(auto const &item:bullets){
        window.draw(*item);
    }
}
void Boss::bullets_move(const sf::Time &elapsed){

    for(auto it=bullets.begin();it!=bullets.end();it++){
        (*it)->bullet_move(elapsed);
        if((*it)->check_border()){
            bullets.erase(it);
            it--;
        }
    }
}
void Boss::check_collision(Character &character,sf::Sound &sound){
    for(auto &item:bullets){
        if(item->getGlobalBounds().intersects(character.getGlobalBounds())){
            character.collision(sound);
        }
    }
}
