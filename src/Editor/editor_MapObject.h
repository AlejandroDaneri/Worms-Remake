
#ifndef WORMS_MAPOBJECT_H
#define WORMS_MAPOBJECT_H

#include <gtkmm/image.h>
#include "editor_Pos.h"

class MapObject {
    Gtk::Image image;
    Pos position;

public:
    MapObject(Gtk::Image image, Pos pos);

    Glib::RefPtr<Gdk::Pixbuf> getImagePixbuf();

    Gtk::Image *getImageWidget();

    void updatePos(double x, double y);

    double getPrintableWidth();

    double getPrintableHeight();

    int turn();

    Pos getPos();
};


#endif //WORMS_MAPOBJECT_H
