//
// Created by JOSHUA HADDAD on 2019-04-11.
//

#include "Vec2.h"
#include "Graphics.h"


class Force {
    Vec2 force_;
    Vec2* position_;

public:
    Graphics arrow_;
    Force(Vec2 force_, Texture vector_texture_);
    void SetPosition(Vec2* position);
    void UpdatePosition();
};


