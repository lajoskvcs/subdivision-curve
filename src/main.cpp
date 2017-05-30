#include <iostream>
#ifdef _WIN32
#include <GLUT/GLUT.h>
#elif __APPLE__
#include <GLUT/GLUT.h>
#elif __linux__
#include <GL/glut.h>
#endif
#include <vector>
#include <cmath>
#include "Point.hpp"

/**
 * Decalrations
 */
const int windowWidth = 1024;
const int windowHeight = 768;

bool displayZero = true;
bool displayOne = true;
bool displayTwo = true;
bool displayThree = true;
bool displayFour = true;

std::vector<Point> points;
std::vector<Point> splitPoints;
Point* clickedPoint = nullptr;

std::vector<std::pair<float,float>> averageMaskVector;

//finomítási paraméter...
int n = 0;

std::vector<Point> q0;
std::vector<Point> q1;
std::vector<Point> q2;
std::vector<Point> q3;
std::vector<Point> q4;

float calculateFactorial(float toCalculate) {
    return (toCalculate > 1) ? toCalculate * calculateFactorial(toCalculate -1) : 1;
}

float binomialCoeficient(float n, float k) {
    if(k < 0 || k > n) {
        throw MATH_ERREXCEPT;
    }
    return calculateFactorial(n)/(calculateFactorial(k)*calculateFactorial(n-k));
}

/**
 * Initalize the program
 */
void init (void) {
    glClearColor (1.0, 1.0, 1.0, 1.0);
    glMatrixMode (GL_PROJECTION);
    gluOrtho2D (0.0, windowWidth, 0.0, windowHeight);
}


void calculateAverageMask(int n) {
    if(n >= 0 && n < points.size()-1) {
        averageMaskVector.clear();
        int maxSize = n+1;
        for(int i = 0; i < maxSize; i++) {

            float weight = binomialCoeficient(n,i)*std::powf(2,-n);
            float offset = i - n/2;
            if(n == 2) {
                std::cout << weight << std::endl << offset << std::endl;
            }
            std::pair<float,float> weightOffset (weight,offset);
            averageMaskVector.push_back(weightOffset);
        }
    }
}

void split() {
    if(points.size() > 2 && n >= 0 && n < points.size() - 1) {
        splitPoints.clear();
        for(int i = 0; i < points.size(); i++) {
            if(i == points.size() -1) {
                Point currentPoint = points.at(i);
                splitPoints.push_back(currentPoint);
                Point p = (currentPoint+points.at(0)) * 0.5;
                splitPoints.push_back(p);
            } else {
                Point currentPoint = points.at(i);
                splitPoints.push_back(currentPoint);
                Point p = (currentPoint+points.at(i+1)) * 0.5;
                splitPoints.push_back(p);
            }
        }
    }
}

int getIndex(int a, int b) {
    int k = (int)points.size();
    int result;
    if(b >= 0) {
        result = (a+b) % (2*k);
    } else {
        result = (a + b + 2*k) % (2*k);
    }
    return result;
}

std::vector<Point> average(int n, Color c) {
    std::vector<Point> tmp;
    if(points.size() > 2 && n >= 0 && n < points.size()-1) {
        calculateAverageMask(n);
        int k = (int)points.size();
        for(int i = 0; i < 2*k; i++) {
            float x = 0;
            float y = 0;
            Point p = Point();
            for(int j = 0; j <= n; j++) {
                int index = getIndex(i,(int)averageMaskVector.at(j).second);
                x += averageMaskVector.at(j).first * splitPoints.at(index).getx();
                y += averageMaskVector.at(j).first * splitPoints.at(index).gety();
            }
            p.setx(x);
            p.sety(y);
            p.setColor(c);
            tmp.push_back(p);
        }
    }
    return tmp;
}

void calculateSubdivisionCurves() {
    q0.clear();
    q1.clear();
    q2.clear();
    q3.clear();
    q4.clear();
    if(n >= 0 && points.size() > 2) {

        q0 = average(0, Color(1,0,0));
    }
    if(n >= 1) {

        q1 = average(1, Color(0,1,0));
    }
    if(n >= 2) {
        q2 = average(2, Color(0,0,1));
    }
    if(n >= 3) {
        q3 = average(3, Color(1,0,1));
    }
    if(n >= 4) {
        q4 = average(4, Color(0,1,1));
    }
}

void drawCurve(std::vector<Point> vector) {
    glBegin(GL_LINE_LOOP);
    for(int i = 0; i < vector.size(); i++) {
        vector[i].getColor().setGlColor();
        glVertex2f(vector[i].getx(), vector[i].gety());
    }
    glEnd();
}

void drawDrawableCurves() {
    if(displayZero) {
        drawCurve(q0);
    }
    if(displayOne) {
        drawCurve(q1);
    }
    if(displayTwo) {
        drawCurve(q2);
    }
    if(displayThree) {
        drawCurve(q3);
    }
    if(displayFour) {
        drawCurve(q4);
    }
}

void drawSubdivisionCurve() {
    glClear(GL_COLOR_BUFFER_BIT);

    split();
    calculateSubdivisionCurves();
    drawDrawableCurves();

    glColor3f(0.0,0.0,0.0);
    glPointSize(6.0);
    glBegin(GL_POINTS);
    for(int i = 0; i < points.size(); i++) {
        glVertex2f(points[i].getx(), points[i].gety());
    }
    glEnd();

    glutSwapBuffers();
}

void keyUp (unsigned char key, int x, int y) {
    if(key == '0') {
        displayZero = !displayZero;
    }
    if(key == '1') {
        displayOne = !displayOne;
    }
    if(key == '2') {
        displayTwo = !displayTwo;
    }
    if(key == '3') {
        displayThree = !displayThree;
    }
    if(key == '4') {
        displayFour = !displayFour;
    }
    if(key == 'q') {
        n = 0;
    }
    if(key == 'w') {
        n = 1;
    }
    if(key == 'e') {
        n = 2;
    }
    if(key == 'r') {
        n = 3;
    }
    if(key == 't') {
        n = 4;
    }

    if(key == 'x') {
        points.clear();
    }

    glutPostRedisplay( );
}

void motionHandler(int x, int y) {
    y = windowHeight - y;
    if (clickedPoint != nullptr) {
        clickedPoint->setx(x);
        clickedPoint->sety(y);
        glutPostRedisplay();
    }
}

void mouseHandler(int button, int state, int x, int y) {
    if (button == GLUT_LEFT) {
        if (state == GLUT_DOWN) {

            Point clickedPointOnWindows{ (float)x, (float)windowHeight - y, Color(1.0,0.0,0.0) };

            for (Point &p: points) {
                if (p.distanceFromPoint(clickedPointOnWindows) < 10.0) {
                    clickedPoint = &p;
                    clickedPoint->setColor(Color(1.0,1.0,0.0));
                }
            }

            if(clickedPoint == nullptr) {
                points.push_back(clickedPointOnWindows);
            }

        } else if (state == GLUT_UP && clickedPoint != nullptr) {
            clickedPoint->setColor(Color(1.0,0.0,0.0));
            clickedPoint = nullptr;
        }
    }
    glutPostRedisplay();
}

int main(int argc, char * argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowPosition(50, 100);
    glutInitWindowSize(windowWidth, windowHeight);
    glutCreateWindow("Subdivision curve");
    init();
    glutDisplayFunc(drawSubdivisionCurve);
    glutMotionFunc(motionHandler);
    glutMouseFunc(mouseHandler);
    glutKeyboardUpFunc(keyUp);
    glutMainLoop ();
    return 0;
}