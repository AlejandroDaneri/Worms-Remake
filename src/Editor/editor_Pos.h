#ifndef WORMS_POSITION_H
#define WORMS_POSITION_H


class Pos {
private:
    double x,y;
    int angle;

    double calculatePos(double x, double size);
public:
    Pos(double x,double y,int angle=0);

    double getPrintableWidth(double size);

    double getPrintableHeigth(double size);

    void updatePos(double x, double y);

    int turn();

    double getX() const;

    double getY() const;

    int getAngle() const;

};
#endif //WORMS_POSITION_H
