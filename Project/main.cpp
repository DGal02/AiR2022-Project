#include <iostream>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "character.h"
#include "fire.h"
#include "enemy.h"
#include "fly.h"
void Create_wall(std::vector<sf::Sprite> &walls, const sf::Texture &texture,int x,int y){
    sf::Sprite wall;
    wall.setTexture(texture);
    wall.setTextureRect(sf::IntRect(0,0,175,25));
    wall.setPosition(x,y);
    walls.emplace_back(wall);
}
void Create_mob_resp(std::vector<sf::Sprite> &mob_resp,const sf::Texture &texture){
    sf::Sprite temp_resp;
    temp_resp.setTexture(texture);
    mob_resp.emplace_back(temp_resp);
}

void Wygrana(sf::RenderWindow &window,sf::Text &text){
    text.setString("WYGRANA!");
    text.setPosition(20,20);
    text.setFillColor(sf::Color::Green);
    window.setView(sf::View(sf::FloatRect(0,0,1600,800)));
    window.clear(sf::Color::Black);
    window.draw(text);
    window.display();
}
void Przegrana(sf::RenderWindow &window,sf::Text &text){
    text.setString("PRZEGRANA!");
    text.setPosition(20,20);
    text.setFillColor(sf::Color::Red);
    window.setView(sf::View(sf::FloatRect(0,0,1600,800)));
    window.clear(sf::Color::Black);
    window.draw(text);
    window.display();
}
void CheckView(sf::RenderWindow &window,sf::View &view,const Fire &fire){
    float x=view.getCenter().x-window.getSize().x/2;
    float y=view.getCenter().y-window.getSize().y/2;
    if(x<0){
        x=0;
    }
    if(x+window.getSize().x>window.getSize().x*1.25){
        x=window.getSize().x*1.25-window.getSize().x;
    }
    if(y<-300){
        y=-300;
    }
    if(y+window.getSize().y>800.f+fire.getGlobalBounds().height){
        y=800.f+fire.getGlobalBounds().height-window.getSize().y;
    }
    window.setView(sf::View(sf::FloatRect(x,y,window.getSize().x,window.getSize().y)));
}

template <class name>
void new_enemy(std::vector<std::unique_ptr<Enemy>> &enemies,const sf::Texture &texture,float x,float y){
    auto temp_obj=std::make_unique<name>(texture);
    temp_obj->setPosition(x,y);
    enemies.emplace_back(std::move(temp_obj));
}

int main() {

    // Initialize variables
    int window_x=1600;
    int window_y=800;
    sf::RenderWindow window(sf::VideoMode(window_x, window_y), "Jump or Die");
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(144);

    std::vector<sf::Sprite> walls;
    std::vector<sf::Sprite> mob_spawns;
    std::vector<std::unique_ptr<Enemy>> enemies;
    sf::Clock clock;
    sf::Clock clock_enemy;
    sf::View view1(sf::FloatRect(0.f, 0.f, window.getSize().x, window.getSize().y));

    //Load textures
    sf::Texture texture;
    if (!texture.loadFromFile("textures/space.png")) {
        return 1;
    }
    texture.setRepeated(true);
    sf::Sprite space;
    space.setTexture(texture);
    space.setTextureRect(sf::IntRect(0, 0, window.getSize().x*1.25, window.getSize().y+300.f));

    sf::Texture texture_character;
    space.setPosition(0,-300);


    if(!texture_character.loadFromFile("textures/guy.png")) { return 1; }
    sf::Texture texture_wall;
    if (!texture_wall.loadFromFile("textures/wall.png")) {
        return 1;
    }
    texture_wall.setRepeated(true);

    sf::Texture texture_mob_resp;
    if(!texture_mob_resp.loadFromFile("textures/mob_resp.png")) {return 1;}

    sf::Texture texture_fire0;
    if(!texture_fire0.loadFromFile("textures/fire0.gif")) {return 1;}
    texture_fire0.setRepeated(true);

    sf::Texture texture_fire1;
    if(!texture_fire1.loadFromFile("textures/fire1.gif")) {return 1;}
    texture_fire1.setRepeated(true);

    sf::Texture texture_fire2;
    if(!texture_fire2.loadFromFile("textures/fire2.gif")) {return 1;}
    texture_fire2.setRepeated(true);

    sf::Texture texture_fire3;
    if(!texture_fire3.loadFromFile("textures/fire3.gif")) {return 1;}
    texture_fire3.setRepeated(true);

    sf::Texture texture_fly;
    if(!texture_fly.loadFromFile("textures/fly.png")) {return 1;}

    sf::Font font;
    // Load it from a file
    if (!font.loadFromFile("czcionka.ttf")) { return 1; }

    //Create Mob Resps
    Create_mob_resp(mob_spawns,texture_mob_resp);
    mob_spawns[0].setPosition(1000.f-(mob_spawns[0].getGlobalBounds().width/2),-300);

    Create_mob_resp(mob_spawns,texture_mob_resp);
    mob_spawns[1].setPosition(0,window.getSize().y/2.f-300.f/2.f-mob_spawns[1].getGlobalBounds().height/2.f);

    Create_mob_resp(mob_spawns,texture_mob_resp);
    mob_spawns[2].setPosition(window.getSize().x*1.25-mob_spawns[2].getGlobalBounds().width,window.getSize().y/2.f-300.f/2.f-mob_spawns[1].getGlobalBounds().height/2.f);

    //Create Walls
    Create_wall(walls,texture_wall,600,200);
    Create_wall(walls,texture_wall,800,500);
    Create_wall(walls,texture_wall,10,700);
    Create_wall(walls,texture_wall,1600,455);
    Create_wall(walls,texture_wall,1250,570);
    Create_wall(walls,texture_wall,1800,750);
    Create_wall(walls,texture_wall,50,175);
    Create_wall(walls,texture_wall,1525,175);



    float width=texture_character.getSize().x;
    float height=texture_character.getSize().y;




    // create some shapes
    //Character
    auto character=std::make_unique<Character>(texture_character);
    character->setPosition(window_x/2-character->getGlobalBounds().width/2,window_y/2);
    //Fire
    Fire fire(texture_fire0,texture_fire1,texture_fire2,texture_fire3);
    fire.setPosition(0,800);
    fire.scale(3.f,3.f);
    fire.setTextureRect(sf::IntRect(0,0,2000.f/3.f,20));
    //Text
    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(250);
    new_enemy<Fly>(enemies,texture_fly,100.f,600.f);
    // run the program as long as the window is open
    while (window.isOpen()) {
        //Przegrana

        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        sf::Time elapsed=clock.restart();
        while (window.pollEvent(event)) {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }
        //Victory/loss
        if(character->przegrana()){
            Przegrana(window,text);
            continue;
        }
        if(character->wygrana()){
            Wygrana(window,text);
            continue;
        }
        //Movement

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {

            character->walk(elapsed,1,view1);
            character->setTextureRect(sf::IntRect(0, 0, texture_character.getSize().x, texture_character.getSize().y));

        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {

            character->walk(elapsed,-1,view1);
            character->setTextureRect(sf::IntRect(texture_character.getSize().x, 0, -texture_character.getSize().x, texture_character.getSize().y));


        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {

            character->set_jump();


        }
        //Gravitation +animations

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
        for(auto &item:enemies){
            item->catch_character(elapsed,character->getGlobalBounds());
            item->animate();
        }

        //window manipulation
        CheckView(window,view1,fire);
        window.clear(sf::Color::Black);


        window.draw(space);
        for(const auto&item:walls){
            window.draw(item);
        }
        for(const auto&item:mob_spawns){
            window.draw(item);
        }
        for(const auto&item:enemies){
            window.draw(*item);
        }
        window.draw(fire);
        window.draw(*character);
        // end the current frame
        window.display();
    }

    return 0;
}
