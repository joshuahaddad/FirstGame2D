
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Graphics.h"
#include "Shape.h"
#include "RigidBody.h"
#include "Vec2.h"
#include "Force.h"
#include <math.h>

using namespace std;
using sf::RenderWindow;

int main()
{
    RenderWindow window(sf::VideoMode(2500, 1500), "Physics!");

    vector<Graphics> items;
    vector<RigidBody*> bodies;

    //Loading space texture and scaling to fit the screen
    Texture space;
    space.loadFromFile("./assets/stars.png");
    Sprite background;
    background.setTexture(space);
    background.setScale(1,1);
    background.scale(2.1,2.2);

    //Loading the force arrow texture for use later
    Texture force_arrow;
    force_arrow.loadFromFile("./assets/vector.png");
    Graphics arrows(force_arrow);

    //Testing force display
    Force vector_test(Vec2(512,512));


    Texture box;
    box.loadFromFile("./assets/boxSprite.png");

    int mass[10] = {10,1000,5000000,5000000,5000000, 100000,100000,100000,100000,100000};
    for(int i = 0; i < 2; i++){
        Material* iron = new Material(mass[i], 0.05);
        ShapeBody* shape = new Rectangle(10,10, *iron);

        shape->SetMass(mass[i]);
        RigidBody* object = new RigidBody(shape);
        object->position_.Reset(i*2500/2, 1500/2*i);

        Graphics* game_item = new Graphics(box);
        game_item->GetSprite()->setScale(.5,.5);
        game_item->GetSprite()->scale(.25,.25);
        game_item->GetSprite()->setOrigin(502/2,502/2);
        game_item->GetSprite()->setPosition(1960/2 + i * 400,1080/2 +i * 200);

        items.push_back(*game_item);
        bodies.push_back(object);
    }

    vector_test.SetPosition(bodies.at(0)->GetPositionPointer());

    Clock clock;

    while (window.isOpen())
    {
        Time time = clock.getElapsedTime();
        float dt = time.asSeconds();
        clock.restart();

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if(sf::Keyboard::isKeyPressed(Keyboard::D)){
            Vec2 forcevector(30.f, 0);
            Force force(forcevector);
            bodies.at(0)->AddForce(force);
        }
        if(sf::Keyboard::isKeyPressed(Keyboard::A)){
            Vec2 forcevector(-30.f, 0);
            Force force(forcevector);
            bodies.at(0)->AddForce(force);

        }
        if(sf::Keyboard::isKeyPressed(Keyboard::S)){
            Vec2 forcevector(0, 30.f);
            Force force(forcevector);
            bodies.at(0)->AddForce(force);
        }
        if(sf::Keyboard::isKeyPressed(Keyboard::W)){
            Vec2 forcevector(0, -30.f);
            Force force(forcevector);
            bodies.at(0)->AddForce(force);
        }

        //if(abs(bodies.at(0)->net_force_.GetX()) > .001 || abs(bodies.at(0)->net_force_.GetY()) > 0.01)


        window.clear(Color(255,255,255));
        window.draw(background);

        for(int i = 0; i < bodies.size(); i++){
            for(int j = 0; j < bodies.size(); j++){
                //if(abs(bodies.at(0)->velocity_.GetX()) > .001 || abs(bodies.at(0)->velocity_.GetY()) > 0.01)
                    //bodies.at(i)->AddDrag(.0001);
                bodies.at(i)->AddGravitational(bodies.at(j));
            }
        }

        for(int i = 0; i < bodies.size(); i++){
            bodies.at(i)->UpdatePhysics(dt);

            //Looping around the screen
            /*if(bodies.at(i)->GetPosition().GetX() < 0){
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
            }*/
            items.at(i).SetPosition(bodies.at(i)->GetPosition());
            items.at(i).GetSprite()->setRotation(items.at(i).GetSprite()->getRotation() + .01);
            window.draw(*items.at(i).GetSprite());
        }

        vector_test.SetOrientation(0);
        window.display();

    }

    return 0;
}