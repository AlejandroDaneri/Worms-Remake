
#include <giomm.h>
#include <iostream>
#include <gdkmm.h>
#include "editor_MapArea.h"
#include "editor_Item.h"

MapArea::MapArea(ToolBox *toolBox) {
    add_events(Gdk::BUTTON_PRESS_MASK);
    this->toolBox =toolBox;
}

bool MapArea::on_draw(const ::Cairo::RefPtr<::Cairo::Context> &cr) {
    for(Item item:items ){
        Gdk::Cairo::set_source_pixbuf
                (cr, item.getImage(), item.getX(),item.getY());
        cr->paint();
    }
    return true;
}

bool MapArea::on_button_press_event(GdkEventButton *button_event) {
    try {
        const std::string &path = toolBox->getActualItemImagePath();
        Glib::RefPtr<Gdk::Pixbuf> new_image = Gdk::Pixbuf::create_from_file(path);
        Item new_item(std::move(new_image),button_event->x,button_event->y);
        items.push_back(std::move(new_item));
    }
    catch(const Gio::ResourceError& ex)
    {
        std::cerr << "ResourceError: " << ex.what() << std::endl;
    }
    catch(const Gdk::PixbufError& ex)
    {
        std::cerr << "PixbufError: " << ex.what() << std::endl;
    }
    queue_draw();
    return true;
}

