
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Graphics.h"
#include "Shape.h"
#include "RigidBody.h"
#include "Vec2.h"
#include <math.h>

using namespace std;
using sf::RenderWindow;

int main()
{
    RenderWindow window(sf::VideoMode(1960, 1080), "Physics!");
    const float fps = 60;
    const float dt = 1/fps;
    float accumulator = 0;

    vector<Graphics> items;
    vector<RigidBody*> bodies;
    Material iron(1, 0.05);
    Rectangle square(10,10, iron);
    ShapeBody* shape = &square;

    Texture box;
    box.loadFromFile("./assets/boxSprite.png");

    for(int i = 0; i < 5; i++){
        RigidBody* object = new RigidBody(shape);
        object->position_.Reset(1960/2 + i * 400, 1080/2 +i * 200);
        Graphics* game_item = new Graphics(box, object);
        game_item->sprite_.setScale(.5,.5);
        game_item->sprite_.scale(.25,.25);
        game_item->sprite_.setOrigin(502/2,502/2);
        game_item->sprite_.setPosition(1960/2 + i * 400,1080/2 +i * 200);

        items.push_back(*game_item);
        bodies.push_back(object);
    }


    float i = 0;

    while (window.isOpen())
    {

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if(sf::Keyboard::isKeyPressed(Keyboard::D)){
                bodies.at(0)->AddForce(Vec2(300.f,0));
            }
            if(sf::Keyboard::isKeyPressed(Keyboard::A)){
                bodies.at(0)->AddForce(Vec2(-300.f,0));

            }
            if(sf::Keyboard::isKeyPressed(Keyboard::S)){
                bodies.at(0)->AddForce(Vec2(0,300.f));
            }
            if(sf::Keyboard::isKeyPressed(Keyboard::W)){
                bodies.at(0)->AddForce(Vec2(0,-300.f));
            }
        }

        if(abs(bodies.at(0)->net_force_.GetX()) > .001 || abs(bodies.at(0)->net_force_.GetY()) > 0.01)
            bodies.at(0)->AddDrag(.01);

        window.clear(Color(0,0,0));

        for(int i = 0; i < bodies.size(); i++){
            for(int j = 0; j < bodies.size(); j++){
                bodies.at(i)->AddGravitational(bodies.at(j));
            }
        }

        for(int i = 0; i < bodies.size(); i++){
            bodies.at(i)->UpdatePhysics(dt);

            //Looping around the screen
            if(bodies.at(i)->GetPosition().GetX() < 0){
                bodies.at(i)->SetX(1959);
            }
            else if(bodies.at(i)->GetPosition().GetX() > 1960){
                bodies.at(i)->SetX(1);
            }
            if(bodies.at(i)->GetPosition().GetY() < 0){
                bodies.at(i)->SetY(1079);
            }
            else if(bodies.at(i)->GetPosition().GetY() > 1080){
                bodies.at(i)->SetY(1);
            }
            items.at(i).SetPosition(bodies.at(i)->GetPosition());
            items.at(i).sprite_.setRotation(items.at(i).sprite_.getRotation() + .01);
            window.draw(items.at(i).sprite_);
        }

        window.display();
        i += 1;

    }

    return 0;
}