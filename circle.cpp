#include "circle.h"

Point Circle::crossLine(Line line, Point nearestPoint) {
    float p, q;
    Point p1, p2;
    if (line.a == 0) {
        p = - 2 * x;
        q = pow(x, 2) + pow(line.b / line.c, 2) - 2 * line.b * y / line.c + pow(y, 2) - pow(r, 2);
        float x1 = (-p + sqrt(pow(p, 2) - 4 * q)) / 2;
        float x2 = (-p - sqrt(pow(p, 2) - 4 * q)) / 2;
        float y = line.b / line.c;
        p1 = Point(x1, y);
        p2 = Point(x2, y);
    } else if (line.c == 0) {
        p = - 2 * y;
        q = pow(line.b / line.a, 2) - (2 * line.b * x) / line.a + pow(x, 2) + pow(y, 2) - pow(r, 2);
        float y1 = (-p + sqrt(pow(p, 2) - 4 * q)) / 2;
        float y2 = (-p - sqrt(pow(p, 2) - 4 * q)) / 2;
        float x = line.b / line.a;
        p1 = Point(x, y1);
        p2 = Point(x, y2);
    } else {
        p = (- 2 * x * pow(line.c, 2) + line.a + 2 * line.a * line.b - 2 * y * line.a * line.c) / pow(line.c, 2);
        q = pow(x, 2) + pow(y, 2) - pow(r, 2) + pow(line.b / line.c, 2) - 2 * y * line.b / line.c;
        float x1 = (-p + sqrt(pow(p, 2) - 4 * q)) / 2;
        float x2 = (-p - sqrt(pow(p, 2) - 4 * q)) / 2;
        p1 = Point(x1, (line.a * x1 + line.b) / line.c);
        p2 = Point(x2, (line.a * x2 + line.b) / line.c);
    }

    if (nearestPoint.distance(p1) > nearestPoint.distance(p2)) {
        return p2;
    }

    return p1;
}
