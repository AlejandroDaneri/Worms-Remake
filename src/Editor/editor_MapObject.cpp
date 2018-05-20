
#include "editor_MapObject.h"

MapObject::MapObject(Gtk::Image image, Pos pos)
        : image(std::move(image)),position(pos)
{
}

Glib::RefPtr<Gdk::Pixbuf> MapObject::getImagePixbuf() {
    return image.get_pixbuf();
}

void MapObject::updatePos(double x, double y) {
    position.updatePos(x,y);
}

Gtk::Image * MapObject::getImageWidget() {
    return &image;
}

double MapObject::getPrintableWidth(int width) {
    return position.getPrintableWidth(width);
}

double MapObject::getPrintableHeight(int height) {
    return position.getPrintableHeigth(height);
}

int MapObject::turn() {
    return position.turn();
}

Pos MapObject::getPos() {
    return position;
}
