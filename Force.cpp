//
// Created by JOSHUA HADDAD on 2019-04-11.
//

#include "Force.h"

const float G = 6.67408 * pow(10, -8);

Force::Force(Vec2 force) {
    force_.SetX(force.GetX());
    force_.SetY(force.GetY());

}

Vec2 Force::GetForce() {
    return force_;
}

Force Force::Gravity(float mass_one, float mass_two, Vec2 position_one, Vec2 position_two) {

    if(mass_two == mass_one)
        return {Vec2(0,0)};

    float r = pow(Vec2::Distance(position_one, position_two),2);
    float magnitude = mass_one*mass_two*G/r;
    Vec2 direction(position_one.GetXDir(), position_one.GetYDir());
    Vec2 force = direction * magnitude;

    return {force};
}

Force Force::Drag(Vec2 velocity, float area, float coefficient) {
    float drag = coefficient*pow(velocity.GetMagnitude(),2)*area/2;
    return {velocity*area};
}
