//
// Created by JOSHUA HADDAD on 2019-04-10.
//

#pragma once
#include "Shape.h"
#include "Vec2.h"


class RigidBody {
public:
    ShapeBody* shape_;

    //Forces
    Vec2 net_force_;

    //Linear
    Vec2 position_;
    Vec2 velocity_;
    Vec2 acceleration_;

    //Angular
    float orientation_;
    float angular_velocity_;
    float torque_;

public:
    RigidBody(ShapeBody* shape);
    void UpdatePhysics(float dt);

    //Forces
    void AddForce(Vec2 force);
    void AddDrag(float scale_factor);
    void AddGravitational(RigidBody* partner);

    //Helper Methods
    float Distance(RigidBody* partner);

    //Setters
    void SetX(float x);
    void SetY(float y);
    void SetVelocity(float x, float y);
    void SetAcceleration(Vec2 a);
    void SetOrientation(float radians);
    void SetAngularVelocity(float omega);
    void SetTorque(float torque);

    Vec2 GetPosition();
    ShapeBody* GetShape();
};

class ChargedBody : public RigidBody{

};

