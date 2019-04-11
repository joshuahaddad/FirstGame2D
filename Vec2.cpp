//
// Created by JOSHUA HADDAD on 2019-04-10.
//

#include "Vec2.h"

Vec2::Vec2() {
    x_ = 0;
    y_ = 0;
    magnitude_ = 0;
    xDir_ = 0;
    yDir_ = 0;
}

Vec2::Vec2(float x, float y) {
    x_ = x;
    y_ = y;
    magnitude_ = sqrt(x*x+y*y);
    xDir_ = abs(x/magnitude_);
    yDir_ = abs(y/magnitude_);
}

bool Vec2::operator==(const Vec2 &rhs) {
    return(xDir_ == rhs.xDir_ && yDir_ == rhs.yDir_);
}

Vec2 Vec2::operator+(const Vec2 &rhs) {
    return Vec2(x_ + rhs.x_, y_ + rhs.y_);
}

Vec2 Vec2::operator-(const Vec2 &rhs) {
    return Vec2(x_ - rhs.x_, y_ - rhs.y_);
}

float Vec2::Cross(const Vec2 &rhs) {
    return (x_ * rhs.y_ - y_ * rhs.x_);
}

float Vec2::Dot(const Vec2 &rhs) {
    return (x_ * rhs.x_ + y_ * rhs.y_);
}

Vec2 Vec2::Cross(const Vec2 &lhs, float rhs) {
    return Vec2(rhs * lhs.y_, -rhs * lhs.x_);
}

Vec2 Vec2::Cross(float lhs, const Vec2 &rhs) {
    return Vec2(-lhs * rhs.y_, lhs * rhs.x_);
}

Vec2 Vec2::operator=(const Vec2 &rhs) {
    return Vec2(rhs.x_, rhs.y_);
}

void Vec2::operator+=(const Vec2 &rhs) {
    x_ += rhs.x_;
    y_ += rhs.y_;
    if(x_ != 0 || y_ != 0){
        magnitude_ = sqrt(x_*x_+y_*y_);
        xDir_ = abs(x_/magnitude_);
        yDir_ = abs(y_/magnitude_);
    } else {
        xDir_ = 0;
        yDir_ = 0;
        magnitude_ = 0;
    }
}

Vec2 Vec2::operator*(float scalar) {
    return Vec2(x_*scalar, y_*scalar);
}

float Vec2::GetX() {
    return x_;
}

float Vec2::GetY() {
    return y_;
}

float Vec2::GetMagnitude(){
    return magnitude_;
}

float Vec2::GetXDir(){
    return((x_ >= 0) ?  xDir_ : -xDir_);
}

float Vec2:: GetYDir(){
    return((y_ >= 0) ?  yDir_ : -yDir_);
}

void Vec2::Reset(float x, float y) {
    x_ = x;
    y_ = y;
    magnitude_ = sqrt(x*x+y*y);
    xDir_ = abs(x/magnitude_);
    yDir_ = abs(y/magnitude_);
}

void Vec2::SetY(float y) {
    y_ = y;
}

void Vec2::SetX(float x) {
    x_ = x;
}

Vec2 Vec2::Direction(Vec2 &partner) {
    return Vec2(x_ - partner.x_, y_ - partner.y_);
}


