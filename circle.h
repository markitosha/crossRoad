#ifndef CIRCLE_H
#define CIRCLE_H

#include "line.h"
#include <cmath>

struct Circle {
    float x;
    float y;
    float r;

    Circle(float r, float x = 0, float y = 0) : x(x), y(y), r(r) {}

    Point crossLine(Line line, Point nearestPoint);
};
#endif // CIRCLE_H
