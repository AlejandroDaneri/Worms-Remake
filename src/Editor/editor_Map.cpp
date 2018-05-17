
#include <gtkmm/builder.h>
#include "editor_Map.h"

Map::Map(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& builder)
        : Gtk::Layout(cobject),
          m_builder(builder)
{
    add_events(Gdk::BUTTON_PRESS_MASK);
    signal_button_press_event().connect(
            sigc::mem_fun(*this,&Map::on_button_clicked));
}


bool Map::on_button_clicked(GdkEventButton *button_event) {
    if(this) {
        Gtk::Image new_image("resources/images/Weapons_icons/Bazooka.png");
        put(new_image, button_event->x, button_event->y);
        new_image.show();
        objects.push_back(std::move(new_image));
    }
    return true;
}

void Map::undo() {
    objects.pop_back();
}

void Map::clean(){
    objects.clear();
}
