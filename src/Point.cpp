//
//  Point.cpp
//  BevgrafNumFour
//
//  Created by Lajos Kovács on 2016. 12. 11..
//  Copyright © 2016. Diwin. All rights reserved.
//

#include "Point.hpp"
#include <cmath>

Point Point::operator-(const Point& rhs) {
    Point result;

    result.x = x - rhs.x;
    result.y = y - rhs.y;

    return result;
}

Point Point::operator+(const Point& rhs) {
    Point result;

    result.x = x + rhs.x;
    result.y = y + rhs.y;

    return result;
}
Point Point::operator*(const float a) {
    Point result;

    result.x = x * a;
    result.y = y * a;

    return result;
}

float Point::distanceFromPoint(const Point& rhs) {
    return std::sqrt(std::pow(x  - rhs.x, 2) + std::pow(y - rhs.y, 2));
}

float Point::getx() {
    return this->x;
}

float Point::gety() {
    return this->y;
}

void Point::setx(float newx) {
    x = newx;
}

void Point::sety(float newy) {
    y = newy;
}

Color Point::getColor() {
    return color;
}

void Point::setColor(Color c) {
    color = c;
}