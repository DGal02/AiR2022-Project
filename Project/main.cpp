#include <iostream>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "character.h"
#include "fire.h"
void Create_wall(std::vector<sf::Sprite> &walls, const sf::Texture &texture,int x,int y){
    sf::Sprite wall;
    wall.setTexture(texture);
    wall.setTextureRect(sf::IntRect(0,0,175,25));
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
        return 1;
    }
    texture_wall.setRepeated(true);

    sf::Texture texture_mob_resp;
    if(!texture_mob_resp.loadFromFile("mob_resp.png")) {return 1;}

    sf::Texture texture_fire0;
    if(!texture_fire0.loadFromFile("fire0.gif")) {return 1;}
    texture_fire0.setRepeated(true);

    sf::Texture texture_fire1;
    if(!texture_fire1.loadFromFile("fire1.gif")) {return 1;}
    texture_fire1.setRepeated(true);

    sf::Texture texture_fire2;
    if(!texture_fire2.loadFromFile("fire2.gif")) {return 1;}
    texture_fire2.setRepeated(true);

    sf::Texture texture_fire3;
    if(!texture_fire3.loadFromFile("fire3.gif")) {return 1;}
    texture_fire3.setRepeated(true);



    //Create Mob Resps
    sf::Sprite resp1;
    resp1.setTexture(texture_mob_resp);
    resp1.setPosition(1000.f-(resp1.getGlobalBounds().width/2),-325-resp1.getGlobalBounds().height);
    mob_spawns.emplace_back(resp1);
    //Create Walls
    Create_wall(walls,texture_wall,600,200);
    Create_wall(walls,texture_wall,800,500);
    Create_wall(walls,texture_wall,10,700);
    Create_wall(walls,texture_wall,1600,455);
    Create_wall(walls,texture_wall,1250,570);
    Create_wall(walls,texture_wall,1800,750);
    Create_wall(walls,texture_wall,50,175);
    Create_wall(walls,texture_wall,1525,175);








    // create some shapes
        //Character
    auto character=std::make_unique<Character>(texture_character);
    character->setPosition(window_x/2-character->getGlobalBounds().width/2,window_y/2);
        //Fire
    Fire fire(texture_fire0,texture_fire1,texture_fire2,texture_fire3);
    fire.setPosition(0,800);
    fire.scale(3.f,3.f);
    fire.setTextureRect(sf::IntRect(0,0,2000.f/3.f,20));
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
        if(character->getGlobalBounds().top+character->getGlobalBounds().height>800){
            character->reduce_life();

        }
        fire.animate();
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
        window.draw(fire);
        window.draw(*character);
        // end the current frame
        window.display();
    }

    return 0;
}
