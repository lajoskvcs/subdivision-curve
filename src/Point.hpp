//
//  Point.hpp
//  BevgrafNumFour
//
//  Created by Lajos Kovács on 2016. 12. 11..
//  Copyright © 2016. Diwin. All rights reserved.
//

#ifndef Point_hpp
#define Point_hpp

#include "Color.hpp"

class Point {

public:
    Point() : color(0,0,0) {}
    Point(float x, float y) : x(x),y(y), color(1.0,1.0,1.0) {}
    Point(float x, float y, Color c) : x(x),y(y), color(c) {}

    Point operator-(const Point& rhs);
    Point operator+(const Point& rhs);
    Point operator*(const float a);
    float distanceFromPoint(const Point& rhs);
    ~Point(){}
    float getx();
    float gety();
    Color getColor();
    void setColor(Color c);
    void setx(float newx);
    void sety(float newy);
private:
    float x, y;
    Color color;

};

#endif /* Point_hpp */
