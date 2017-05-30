//
//  Color.cpp
//  BevgrafNumFour
//
//  Created by Lajos Kovács on 2016. 12. 11..
//  Copyright © 2016. Diwin. All rights reserved.
//

#include "Color.hpp"


GLfloat Color::getr() {
    return r;
}
GLfloat Color::getg() {
    return g;
}
GLfloat Color::getb() {
    return b;
}

void Color::setr(GLfloat newr) {
    r = newr;
}

void Color::setg(GLfloat newg) {
    g = newg;
}

void Color::setb(GLfloat newb) {
    b = newb;
}

void Color::setGlColor() {
    glColor3f(r, g, b);
}

bool Color::operator==(const Color other) {
    if(r == other.r) {
        return false;
    }
    if(g == other.g) {
        return false;
    }
    if(b == other.b) {
        return false;
    }
    return true;
}


bool Color::isNotWhite() {
    if(r != 1.0 && g != 1.0 && b != 1.0) {
        return true;
    }
    return false;
}
