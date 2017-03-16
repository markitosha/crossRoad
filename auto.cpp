#include "auto.h"

Auto::Auto(int cX, int cY, int r, int sp, int bR, int eR): QGraphicsEllipseItem(0),
    centerX(cX), centerY(cY), radius(r), speed(sp), beginRoad(bR), endRoad(eR) {
    color = QColor(0, 0, 0);
    setBrush(color);
    setRect(0, 0, radius, radius);
    setPos(centerX, centerY);
}

Auto::Auto(const Auto &obj)
{
    this->centerX = obj.centerX;
    this->centerY = obj.centerY;
    this->radius = obj.radius;
    this->speed = obj.speed;
    this->beginRoad = obj.beginRoad;
    this->endRoad = obj.endRoad;
    this->color = obj.color;
}

void Auto::advance(int phase) {
    if (phase) {
        moveBy(0, speed);
    }
}
