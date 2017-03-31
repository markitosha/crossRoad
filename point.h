#ifndef POINT_H
#define POINT_H

#include <cmath>

struct Point {
    float x;
    float y;

    Point(float x = 0, float y = 0) : x(x), y(y) {}

    float distance(Point p) {
        return sqrt(pow((p.x - x), 2) + pow((p.y - y), 2));
    }
};

#endif // POINT_H
