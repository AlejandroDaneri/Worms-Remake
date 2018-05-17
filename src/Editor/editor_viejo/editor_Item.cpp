
#include <glibmm/refptr.h>
#include <gdkmm/pixbuf.h>
#include "editor_Item.h"

Item::Item(const Glib::RefPtr<Gdk::Pixbuf> &&image, double x_pos, double y_pos):
        x(x_pos-image->get_width()/2), y(y_pos-image->get_height()/2) {
    this->image=image;
}

const Glib::RefPtr<Gdk::Pixbuf> Item::getImage() {
    return image;
}

double Item::getX() {
    return x;
}

double Item::getY() {
    return y;
}
