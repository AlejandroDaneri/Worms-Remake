
#ifndef PROJECT_ITEM_H
#define PROJECT_ITEM_H


class Item {
private:
    Glib::RefPtr<Gdk::Pixbuf> image;
    const double x,y;
public:
    Item(const Glib::RefPtr <Gdk::Pixbuf> &&image, double x_pos, double y_pos);

    const Glib::RefPtr<Gdk::Pixbuf> getImage();

    double getX();

    double getY();
};


#endif //PROJECT_ITEM_H
