
#include <gtkmm/builder.h>
#include <gtkmm/scrolledwindow.h>
#include "editor_Map.h"

Map::Map(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& builder)
        : Gtk::Layout(cobject),
          m_builder(builder),
          action(0)
{
    add_events(Gdk::BUTTON_PRESS_MASK);
    signal_button_press_event().connect(
            sigc::mem_fun(*this,&Map::on_button_clicked));
    button_id=1;
    pallete.insert(std::make_pair(1,"resources/images/right_worm.png"));
    pallete.insert(std::make_pair(2,"resources/images/Girder/girder_3.png"));
}


bool Map::on_button_clicked(GdkEventButton *button_event) {
    if(action==0) {
        Gtk::Image new_image(pallete.find(button_id)->second);
        put(new_image, button_event->x, button_event->y);
        new_image.show();
        objects.push_back(std::move(new_image));
        Gtk::ScrolledWindow* map= nullptr;
        m_builder->get_widget("mapw",map);
    } else if(action==1){
        move(objects.back(),button_event->x,button_event->y);
        action=0;
    }
    return true;
}

void Map::undo() {
    objects.pop_back();
}

void Map::clean(){
    objects.clear();
}

void Map::clicked_signal(unsigned int id) {
    button_id=id;
}

void Map::move_signal() {
    action=1;
}
