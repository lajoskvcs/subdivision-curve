//
//  Color.hpp
//  BevgrafNumFour
//
//  Created by Lajos Kovács on 2016. 12. 11..
//  Copyright © 2016. Diwin. All rights reserved.
//

#ifndef Color_hpp
#define Color_hpp

#include <GLUT/glut.h>

class Color {
private:
    GLfloat r, g, b;
public:
    Color(GLfloat r, GLfloat g, GLfloat b): r(r), g(g), b(b) {}
    ~Color(){}

    void setGlColor();
    void setr(GLfloat newr);
    void setg(GLfloat newg);
    void setb(GLfloat newb);
    GLfloat getr();
    GLfloat getg();
    GLfloat getb();

    bool operator==(const Color other);
    bool isNotWhite();
};


#endif /* Color_hpp */
