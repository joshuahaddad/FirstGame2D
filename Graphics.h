#include <iostream>
#include <SFML/Graphics.hpp>
#include "RigidBody.h"

using namespace std;
using namespace sf;

#pragma once

class Graphics {
public:
    Sprite sprite_;
    Texture texture_;

public:
    Graphics(Texture texture, RigidBody* body);
    void SetPosition(Vec2 pos);
};



