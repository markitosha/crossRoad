#include "line.h"
#include <stdio.h>

Line::Line(Point entry, Point end) {
    if (end.x == entry.x) {
        a = 1;
        c = 0;
        b = - entry.x;
    } else if (end.y == entry.y) {
        a = 0;
        c = 1;
        b = entry.y;
    } else {
        a = (end.y - entry.y) / (end.x - entry.x);
        b = - a * entry.x + entry.y;
        c = 1;
    }
}

Line Line::perpendicular(Point p) {
    if (c == 0) {
        return Line(0, p.y, 1);
    }

    if (a == 0) {
        return Line(1, - p.x, 0);
    }

    return Line(- 1 / a, 1 / a * p.x + p.y, 1);
}

Point Line::crossLine(Line line) {
    float x = -100, y = -100;

    if (c == 0) {
        y = line.b;
    }

    if (line.c == 0) {
        y = b;
    }

    if (a == 0) {
        x = - line.b;
    }

    if (line.a == 0) {
        x = - b;
    }

    if (x == -100) {
        x = (line.b - b) / (a - line.a);
    }

    if (y == -100) {
        y = a * x + b;
    }

    return Point(x, y);
}
