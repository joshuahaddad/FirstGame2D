//
// Created by JOSHUA HADDAD on 2019-04-17.
//

#include "Collision.h"

bool Collision::CheckCollision(FloatRect &body_one, FloatRect &body_two) {
    return body_one.intersects(body_two);
}
