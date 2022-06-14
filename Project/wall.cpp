#include "wall.h"

Wall::Wall()
{
    to_collect=false;
    outline.setOutlineColor(sf::Color::Red);
    outline.setOutlineThickness(2.f);
}
bool Wall::get_to_collect(){
    return to_collect;
}
void Wall::set_to_collect(){
    outline.setSize(sf::Vector2f(getGlobalBounds().width+4.f,getGlobalBounds().height+4.f));
    outline.setPosition(getPosition().x-2.f,getPosition().y-2.f);
    to_collect=true;
}
sf::RectangleShape Wall::get_outline(){
    return outline;
}
void Wall::reset(){
    to_collect=false;
}
