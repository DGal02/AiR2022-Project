#include "shoter.h"

Shoter::Shoter(const sf::Texture &texture) :Enemy(texture)
{
    scalar_speed=100;
    hp=1;
    setScale(0.2,0.2);
}

void Shoter::draw_bullets(sf::RenderWindow &window){
    for(auto const &item:bullets){
        window.draw(*item);
    }
}
void Shoter::create_bullet(const sf::FloatRect &bounds){
    if(bullet_timer.getElapsedTime().asSeconds()<3.0){
        return;
    }
    bullet_timer.restart();
    std::unique_ptr<Bullet> temp_bullet=std::make_unique<Bullet>(sf::Vector2i(bounds.left+bounds.width/2,bounds.top+bounds.height/2),getGlobalBounds());
    temp_bullet->setRadius(15);
    temp_bullet->setFillColor(sf::Color::White);
    bullets.emplace_back(std::move(temp_bullet));
}
void Shoter::bullets_move(const sf::Time &elapsed){

    for(auto it=bullets.begin();it!=bullets.end();it++){
        (*it)->bullet_move(elapsed);
        if((*it)->check_border()){
            bullets.erase(it);
            it--;
        }
    }
}
void Shoter::check_collision(Character &character, sf::Sound &sound){
    for(auto it=bullets.begin();it!=bullets.end();it++){
        if(character.getGlobalBounds().intersects((*it)->getGlobalBounds())){
            character.collision(sound);
            bullets.erase(it);
            it--;
        }
    }
}
