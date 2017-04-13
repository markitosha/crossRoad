#include "circle.h"
#include <stdio.h>

Point Circle::crossLine(Line line, Point nearestPoint) {
    float p, q, k;
    Point p1, p2;
    printf("%f %f %f %f %f %f \n", x, y, r, line.a, line.b, line.c);

    if (line.c == 0) {
        p = - 2 * y;
        q = pow(line.b / line.a, 2) + 2 * line.b * x / line.a + pow(x, 2) + pow(y, 2) - pow(r, 2);
        float y1 = (- p + sqrt(pow(p, 2) - 4 * q)) / 2;
        float y2 = (- p - sqrt(pow(p, 2) - 4 * q)) / 2;
        float x = - line.b / line.a;
        p1 = Point(x, y1);
        p2 = Point(x, y2);
    } else {
        k = 1 + pow(line.a / line.c, 2);
        p = 2 * line.a * line.b / pow(line.c, 2)  - 2 * x - 2 * y * line.a / line.c;
        q = pow(x, 2) + pow(y, 2) + pow(line.b / line.c, 2) - 2 * y * line.b / line.c - pow(r, 2);
        float x1 = (-p + sqrt(pow(p, 2) - 4 * k * q)) / (2 * k);
        float x2 = (-p - sqrt(pow(p, 2) - 4 * k * q)) / (2 * k);
        p1 = Point(x1, (line.a * x1 + line.b) / line.c);
        p2 = Point(x2, (line.a * x2 + line.b) / line.c);
    }

    printf("%f %f\n", p, q);

    if (nearestPoint.distance(p1) > nearestPoint.distance(p2)) {
        return p2;
    }

    return p1;
}
