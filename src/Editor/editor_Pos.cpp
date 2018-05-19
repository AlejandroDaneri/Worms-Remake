#include "editor_Pos.h"

Pos::Pos(const int x, const int y):x(x),y(y){
}

int Pos::getPrintableWidth(int size) {
    return calculatePos(x,size);
}
int Pos::getPrintableHeigth(int size) {
    return calculatePos(y,size);
}
int Pos::calculatePos(int x, int size) {
    return x-size/2;
}