#ifndef WORMS_POSITION_H
#define WORMS_POSITION_H


class Pos {
private:
    double x,y;
    int angle;

    double calculatePos(double x, double size);
public:
    Pos(double x,double y);

    double getPrintableWidth(double size);

    double getPrintableHeigth(double size);

    void updatePos(double x, double y);

    int turn();

};
#endif //WORMS_POSITION_H
