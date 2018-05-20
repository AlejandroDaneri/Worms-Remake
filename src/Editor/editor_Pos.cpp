#include "editor_Pos.h"

Pos::Pos(const double x, const double y):x(x),y(y),angle(0){
}

double Pos::getPrintableWidth(double size) {
    return calculatePos(x,size);
}
double Pos::getPrintableHeigth(double size) {
    return calculatePos(y,size);
}
double Pos::calculatePos(double x, double size) {
    return x-size/2;
}

void Pos::updatePos(double x, double y) {
    this->x=x;
    this->y=y;

}

int Pos::turn() {
     return angle+=10;
}

double Pos::getX() const {
    return x;
}

double Pos::getY() const {
    return y;
}

int Pos::getAngle() const {
    return angle;
}


