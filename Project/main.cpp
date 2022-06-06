#include <iostream>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "character.h"
#include "fire.h"
#include "enemy.h"
#include "fly.h"
#include "bullet.h"
#include "boss.h"
#include "ghost.h"
void title_screen(){
    sf::Font bloody;
    if (!bloody.loadFromFile("fonts/BLOODY.ttf")) { return; }

    sf::Text title;
    title.setFont(bloody);
    title.setCharacterSize(55);
    title.setString("JUMP OR DIE");
    title.setPosition(400-title.getGlobalBounds().width/2.f,100);


    sf::Text start;
    start.setFont(bloody);
    start.setCharacterSize(35);
    start.setString("START");
    start.setPosition(400-start.getGlobalBounds().width/2,300);

    sf::RectangleShape outline_start;
    outline_start.setPosition(start.getGlobalBounds().left-2,start.getGlobalBounds().top-2);
    outline_start.setSize(sf::Vector2f(start.getGlobalBounds().width+4,start.getGlobalBounds().height+4));
    outline_start.setFillColor(sf::Color::Black);
    outline_start.setOutlineColor(sf::Color::Red);
    outline_start.setOutlineThickness(3);

    sf::RenderWindow window(sf::VideoMode(800, 600), "My window",sf::Style::Titlebar | sf::Style::Close);

    sf::Cursor cursor;
    if (cursor.loadFromSystem(sf::Cursor::Hand))
        window.setMouseCursor(cursor);
    sf::Cursor::Type cursor_type=sf::Cursor::Hand;


    while (window.isOpen()) {

        sf::Event event;
        while (window.pollEvent(event)) {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonPressed) {
                //Left click event
                if(event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
                    sf::FloatRect rectangle_bounds=outline_start.getGlobalBounds();

                    if(( (rectangle_bounds.left<=mouse_pos.x) && ( (rectangle_bounds.left+rectangle_bounds.width) >=mouse_pos.x )) &&
                            ( (rectangle_bounds.top<=mouse_pos.y) && ( (rectangle_bounds.top + rectangle_bounds.height) >=mouse_pos.y )))
                    {
                        window.close();
                    }
                }
            }
        }
        //Check if cursor in Start button
        sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
        sf::FloatRect rectangle_bounds=outline_start.getGlobalBounds();

        if(( (rectangle_bounds.left<=mouse_pos.x) && ( (rectangle_bounds.left+rectangle_bounds.width) >=mouse_pos.x )) &&
                ( (rectangle_bounds.top<=mouse_pos.y) && ( (rectangle_bounds.top + rectangle_bounds.height) >=mouse_pos.y )))
        {
            outline_start.setOutlineColor(sf::Color::Green);
            if(cursor_type!=sf::Cursor::Hand){
                if (cursor.loadFromSystem(sf::Cursor::Hand)){

                    window.setMouseCursor(cursor);
                    cursor_type=sf::Cursor::Hand;
                }
            }

        } else {
            outline_start.setOutlineColor(sf::Color::Red);
            if(cursor_type!=sf::Cursor::Arrow){
                if (cursor.loadFromSystem(sf::Cursor::Arrow)){

                    window.setMouseCursor(cursor);
                    cursor_type=sf::Cursor::Arrow;
                }
            }
        }

        window.clear(sf::Color::Black);
        window.draw(outline_start);
        window.draw(title);
        window.draw(start);


        window.display();
    }
}
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
float get_left_view(const sf::RenderWindow &window){
    return (window.getView().getCenter().x-window.getView().getSize().x/2);
}
float get_top_view(const sf::RenderWindow &window){
    return (window.getView().getCenter().y-window.getView().getSize().y/2);
}
int main() {
    title_screen();
    // Initialize variables
    int window_x=1600;
    int window_y=800;
    sf::RenderWindow window(sf::VideoMode(window_x, window_y), "Jump or Die",sf::Style::Titlebar | sf::Style::Close);
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(144);

    std::vector<sf::Sprite> walls;
    std::vector<sf::Sprite> mob_spawns;
    std::vector<std::unique_ptr<Enemy>> enemies;
    std::vector<std::unique_ptr<Bullet>> bullets;
    sf::Clock clock;
    sf::Clock clock_enemy;
    sf::Clock clock_gun;
    sf::View view1(sf::FloatRect(0.f, 0.f, window.getSize().x, window.getSize().y));
    bool first_while=true;

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

    sf::Texture texture_boss;
    if(!texture_boss.loadFromFile("textures/boss.png")) {return 1;}

    sf::Texture texture_ghost;
    if(!texture_ghost.loadFromFile("textures/duch.png")) {return 1;}

    sf::Font font;
    if (!font.loadFromFile("czcionka.ttf")) { return 1; }


    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile("uderzenie2.wav"))
    {return -1;}
    sf::Sound sound(buffer);

    sf::SoundBuffer gun_s;
    if(!gun_s.loadFromFile("piu.wav")){
        return 1;
    }
    sf::Sound gun_sound(gun_s);


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



    //Character
    auto character=std::make_unique<Character>(texture_character);
    character->setPosition(window_x/2-character->getGlobalBounds().width/2,window_y/2);

    //Boss
    auto boss=std::make_unique<Boss>(texture_boss);
    //Fire
    Fire fire(texture_fire0,texture_fire1,texture_fire2,texture_fire3);
    fire.setPosition(0,800);
    fire.scale(3.f,3.f);
    fire.setTextureRect(sf::IntRect(0,0,2000.f/3.f,20));
    //Text
    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(250);

    sf::Text text_hp;
    text_hp.setFont(font);
    text_hp.setCharacterSize(25);


    // run the program as long as the window is open
    while (window.isOpen()) {

        if(clock.getElapsedTime().asSeconds()>=1){
            clock.restart();
        }
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        sf::Time elapsed=clock.restart();
        if(first_while){
            first_while=false;
            continue;
        }
        while (window.pollEvent(event)) {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
            if(character->przegrana()||character->wygrana()){
                break;
            }
            //Shoot
            if (event.type == sf::Event::MouseButtonPressed) {
                if(event.mouseButton.button == sf::Mouse::Left &&clock_gun.getElapsedTime().asSeconds()>=0.3) {
                    clock_gun.restart();
                    sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
                    mouse_pos.x+=get_left_view(window);
                    mouse_pos.y+=get_top_view(window);

                    bullets.emplace_back(std::make_unique<Bullet>(mouse_pos,character->getGlobalBounds()));
                    gun_sound.play();
                }
            }
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
        boss->boss_move(elapsed);
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
        fire.animate();
        for(auto &item:enemies){
            item->catch_character(elapsed,character->getGlobalBounds());
            item->animate();
        }
        for(auto &item:bullets) {
            item->bullet_move(elapsed);
        }
        //Collision check

        for(const auto &item:enemies){
            if(character->getGlobalBounds().intersects(item->getGlobalBounds())){
                character->collision(sound);
            }
        }

        for(auto it1=bullets.begin();it1!=bullets.end();it1++){

            for(auto it2=enemies.begin();it2!=enemies.end();it2++){
                if((*it1)->getGlobalBounds().intersects((*it2)->getGlobalBounds())){
                    (*it2)->reduce_life();
                    if((*it2)->get_hp()<=0){
                        enemies.erase(it2);
                        it2--;
                        character->add_points();
                    }

                    bullets.erase(it1);
                    it1--;
                    break;
                }


            }

        }

        for(auto it=bullets.begin();it!=bullets.end();it++){


            if((*it)->check_border()){
                bullets.erase(it);
                it--;


            }

        }

        if(character->getGlobalBounds().intersects(fire.getGlobalBounds())){
            character->reduce_life(sound,character->get_hp());


        }

        //New enemy
        if(clock_enemy.getElapsedTime().asSeconds()>=1.0){
            clock_enemy.restart();
            int random_number=rand()%3;
            switch(random_number){
            case 0:
                new_enemy<Ghost>(enemies,texture_ghost,mob_spawns[random_number].getGlobalBounds().left+mob_spawns[random_number].getGlobalBounds().width/2, mob_spawns[random_number].getGlobalBounds().top+mob_spawns[random_number].getGlobalBounds().height/2);
                break;

            case 1:
                new_enemy<Fly>(enemies,texture_fly,mob_spawns[random_number].getGlobalBounds().left+mob_spawns[random_number].getGlobalBounds().width/2, mob_spawns[random_number].getGlobalBounds().top+mob_spawns[random_number].getGlobalBounds().height/2);
                break;
            case 2:
                new_enemy<Fly>(enemies,texture_fly,mob_spawns[random_number].getGlobalBounds().left+mob_spawns[random_number].getGlobalBounds().width/2, mob_spawns[random_number].getGlobalBounds().top+mob_spawns[random_number].getGlobalBounds().height/2);;
                break;


            }
        }
        //view manipulation
        CheckView(window,view1,fire);
        //GUI
        std::string text_to_draw="HP: ";
        text_to_draw+=std::to_string(character->get_hp());
        text_to_draw+=" POINTS: ";
        text_to_draw+=std::to_string(character->get_points());
        if(character->immortal()){
            text_to_draw+=" ";
            text_to_draw+="IMMORTAL";
        }
        text_hp.setString(text_to_draw);
        text_hp.setPosition(get_left_view(window),get_top_view(window));
        //Draw
        window.clear(sf::Color::Black);


        window.draw(space);
        for(const auto&item:walls){
            window.draw(item);
        }
        for(const auto&item:mob_spawns){
            window.draw(item);
        }
        for(const auto&item:bullets){
            window.draw(*item);
        }
        for(const auto&item:enemies){
            window.draw(item->get_rectangle_hp());
            window.draw(*item);
        }
        window.draw(text_hp);
        window.draw(fire);
        window.draw(*boss);
        window.draw(*character);
        // end the current frame
        window.display();
    }
    return 0;
}
