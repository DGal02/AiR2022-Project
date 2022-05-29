#include <SFML/Graphics.hpp>

#pragma once

class Fire : public sf::Sprite
{
private:
    std::vector<sf::Texture> frames;
    int current_frame;
    sf::Clock clock;
public:
    Fire(sf::Texture frame0,sf::Texture frame1,sf::Texture frame2,sf::Texture frame3);
    void animate();
};


