#ifndef LINE_H
#define LINE_H

#include "point.h"

struct Line {
    float a;
    float b;
    float c;

    Line(float a = 0, float b = 0, float c = 1) : a(a), b(b), c(1) {}

    Line(Point entry, Point end);

    Line perpendicular(Point p);

    Point crossLine(Line line);
};

#endif // LINE_H
