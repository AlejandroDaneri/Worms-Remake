
#include <giomm.h>
#include <iostream>
#include <gdkmm.h>
#include "editor_MapArea.h"

MapArea::MapArea() {
    add_events(Gdk::BUTTON_PRESS_MASK);
    ok=false;
    try
    {
        new_image = Gdk::Pixbuf::create_from_file("resources/images/right_worm.png");
    }
    catch(const Gio::ResourceError& ex)
    {
        std::cerr << "ResourceError: " << ex.what() << std::endl;
    }
    catch(const Gdk::PixbufError& ex)
    {
        std::cerr << "PixbufError: " << ex.what() << std::endl;
    }
}

bool MapArea::on_draw(const ::Cairo::RefPtr<::Cairo::Context> &cr) {
    cr->set_source_rgb(1, 1, 0); //para ver donde esta
    cr->rectangle(0, 0, get_width(), get_height());
    cr->fill();
    if (ok) Gdk::Cairo::set_source_pixbuf(cr, new_image,x,y);
    cr->paint();
    return true;
}

bool MapArea::on_button_press_event(GdkEventButton *button_event) {
    ok =true;
    this->x=button_event->x;
    this->y=button_event->y;
    queue_draw();
    return true;
}
