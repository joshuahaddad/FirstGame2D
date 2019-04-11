//
// Created by JOSHUA HADDAD on 2019-04-10.
//

#include "RigidBody.h"

RigidBody::RigidBody(ShapeBody* shape) {
    net_force_ = Vec2();

    shape_ = shape;
    position_ = Vec2();

    velocity_ = Vec2();
    acceleration_ = Vec2();

    orientation_ = 0;
    angular_velocity_ = 0;
    torque_ = 0;


}

void RigidBody::UpdatePhysics(float dt) {
    //Calculate position
    float max_speed = 30;

    //Calculate new acceleration and velocity
    Vec2 force = net_force_*shape_->GetInvMass();
    acceleration_ += force;
    velocity_ += acceleration_;
    position_ += velocity_*dt;

    if(abs(velocity_.GetX()) > max_speed){
        velocity_.GetX() > 0 ? velocity_.SetX(max_speed) : velocity_.SetX(-max_speed);
    }
    if(abs(velocity_.GetY()) > max_speed){
        velocity_.GetY() > 0 ? velocity_.SetY(max_speed) : velocity_.SetY(-max_speed);
    }

    //Calculate rotation

    //Set force = 0 and acceleration to 0;
    net_force_.Reset(0,0);
    acceleration_.Reset(0,0);
}

void RigidBody::SetVelocity(float x, float y) {
    velocity_ = Vec2(x,y);
}

void RigidBody::SetAcceleration(Vec2 a) {
    acceleration_ = a;
}

void RigidBody::SetOrientation(float radians) {
    orientation_ = radians;
}

void RigidBody::SetAngularVelocity(float omega) {
    angular_velocity_ = omega;
}

void RigidBody::SetTorque(float torque) {
    torque_ = torque;
}

void RigidBody::AddForce(Vec2 force) {
    net_force_ += force;
}

Vec2 RigidBody::GetPosition() {
    return position_;
}

void RigidBody::AddDrag(float scale_factor) {
    float drag = scale_factor*velocity_.GetMagnitude() * velocity_.GetMagnitude() / 2 * shape_->GetArea();
    Vec2 direction = Vec2(-velocity_.GetXDir(), -velocity_.GetYDir());
    Vec2 drag_force = direction * drag;
    AddForce(drag_force);

}

void RigidBody::SetX(float x) {
    position_.SetX(x);
}

void RigidBody::SetY(float y) {
    position_.SetY(y);
}

void RigidBody::AddGravitational(RigidBody* partner) {
    const float G = 6.67408 * pow(10, -9);
    float r_squared = pow(Distance(partner), 2);
    float m1 = shape_->GetMass();
    float m2 = partner->GetShape()->GetMass();
    float force_magnitude = m1*m2*G/r_squared;

    Vec2 pos_one = GetPosition();
    Vec2 pos_two = partner->GetPosition();
    Vec2 direction = pos_one.Direction(pos_two);
    float x = 0;
    float y = 0;
    if(direction.GetX() != 0)
        x = direction.GetX()/direction.GetMagnitude();
    if(direction.GetY() != 0)
        y = direction.GetY()/direction.GetMagnitude();
    if(r_squared == 0)
        force_magnitude = 0;

    AddForce(Vec2(-x*force_magnitude,-y * force_magnitude));


}

float RigidBody::Distance(RigidBody *partner) {
    float delta_x = pow(position_.GetX() - partner->position_.GetX(),2);
    float delta_y = pow(position_.GetY() - partner->position_.GetY(),2);
    return sqrt(delta_x+delta_y);
}

ShapeBody *RigidBody::GetShape() {
    return shape_;
}
