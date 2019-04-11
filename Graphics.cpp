//
// Created by JOSHUA HADDAD on 2019-04-10.
//

#include "Graphics.h"

Graphics::Graphics(Texture texture) {
    texture_ = texture;
    sprite_.setTexture(texture_);

}

void Graphics::SetPosition(Vec2 pos) {
    sprite_.setPosition(pos.GetX(),pos.GetY());
}
