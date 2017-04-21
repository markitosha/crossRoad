#ifndef LINE_H
#define LINE_H

#include "point.h"

struct Line {
    float a;
    float b;
    float c;

    Line(float a = 0, float b = 0, float c = 1) : a(a), b(b), c(c) {}

    Line(Point entry, Point end);

    Line perpendicular(Point p);

    Point crossLine(Line line);

    float apply(Point p) {
        return c * p.y - a * p.x - b;
    }
};

#endif // LINE_H
