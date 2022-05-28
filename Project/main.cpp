#include <iostream>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "character.h"
void Create_wall(std::vector<sf::Sprite> &walls, const sf::Texture &texture,int x,int y){
    sf::Sprite wall;
    wall.setTexture(texture);
    wall.setTextureRect(sf::IntRect(0,0,200,35));
    wall.setPosition(x,y);
    walls.emplace_back(wall);
}
int window_x=1600;
int window_y=800;
int main() {

    // Initialize variables
    sf::RenderWindow window(sf::VideoMode(window_x, window_y), "Jump or Die");
    window.setVerticalSyncEnabled(true);
    std::vector<sf::Sprite> walls;
    std::vector<sf::Sprite> mob_spawns;
    sf::Clock clock;
    sf::View view1(sf::FloatRect(0.f, 0.f, 1600.f, 800.f));

    //Load textures
    sf::Texture texture;
    if (!texture.loadFromFile("space.png")) {
        std::cerr << "Could not load texture" << std::endl;
        return 1;
    }
    texture.setRepeated(true);
    sf::Sprite space;
    space.setTexture(texture);
    space.setTextureRect(sf::IntRect(0, 0, 2000, 1100));

    sf::Texture texture_character;
    space.setPosition(0,-300);


    if(!texture_character.loadFromFile("guy.png")) { return 1; }
    sf::Texture texture_wall;
    if (!texture_wall.loadFromFile("wall.png")) {
        std::cerr << "Could not load texture" << std::endl;
        return 1;
    }
    texture_wall.setRepeated(true);

    sf::Texture texture_mob_resp;
    if(!texture_mob_resp.loadFromFile("mob_resp.png")) {return 1;}
    //Create Mob Resps
    sf::Sprite resp1;
    resp1.setTexture(texture_mob_resp);
    resp1.setPosition(1000.f-(resp1.getGlobalBounds().width/2),-325-resp1.getGlobalBounds().height);
    mob_spawns.emplace_back(resp1);
    //Create Walls
    Create_wall(walls,texture_wall,800,200);
    Create_wall(walls,texture_wall,800,500);
    Create_wall(walls,texture_wall,10,700);








    // create some shapes

    auto character=std::make_unique<Character>(texture_character);
    character->setPosition(window_x/2-character->getGlobalBounds().width/2,window_y/2);
    // run the program as long as the window is open

    while (window.isOpen()) {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        sf::Time elapsed=clock.restart();
        while (window.pollEvent(event)) {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }
        //Movement
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {

            character->walk(elapsed,1,view1);

        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {

            character->walk(elapsed,-1,view1);


        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {

            character->set_jump();


        }
        //Gravitation
        character->set_ground_false();
        for(const auto &item:walls){
            if(character->on_ground()){
                break;
            }
            character->check_left(item,elapsed);
            character->check_right(item,elapsed);

        }
        character->gravitation(elapsed,view1);
        character->jump(elapsed,view1);
        //window manipulation
        window.setView(view1);


        window.clear(sf::Color::Black);


        window.draw(space);
        for(const auto&item:walls){
            window.draw(item);
        }
        for(const auto&item:mob_spawns){
            window.draw(item);
        }
        window.draw(*character);
        // end the current frame
        window.display();
    }

    return 0;
}
