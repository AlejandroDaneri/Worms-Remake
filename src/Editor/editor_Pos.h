#ifndef WORMS_POSITION_H
#define WORMS_POSITION_H


class Pos {
private:
    int x,y;

    int calculatePos(int x, int size);
public:
    Pos(int x,int y);

    int getPrintableWidth(int size);

    int getPrintableHeigth(int size);
};
#endif //WORMS_POSITION_H
