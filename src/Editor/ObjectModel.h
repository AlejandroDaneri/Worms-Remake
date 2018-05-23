
#ifndef WORMS_OBJECTMODEL_H
#define WORMS_OBJECTMODEL_H


class ObjectModel {
    double x, y;
    int angle;
public:
    ObjectModel(const double &x, const double &y, const int &angle = 0);

    void updatePosition(double x, double y);

    int turn();

    void getPosition(double &x, double &y);
};


#endif //WORMS_OBJECTMODEL_H
