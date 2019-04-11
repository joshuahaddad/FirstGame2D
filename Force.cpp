//
// Created by JOSHUA HADDAD on 2019-04-11.
//

#include "Force.h"

Force::Force(Vec2 force, Texture vector_texture_) : arrow_(vector_texture_) {
    force_ = force;

    arrow_.GetSprite()->setScale(.25,1);
    arrow_.GetSprite()->setOrigin(256,0);
}

void Force::SetPosition(Vec2 *position) {
    position_ = position;
}

void Force::UpdatePosition(){
    arrow_.SetPosition(*position_);
}
