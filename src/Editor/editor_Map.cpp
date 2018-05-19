
#include <gtkmm/builder.h>
#include <gtkmm/scrolledwindow.h>
#include <iostream>
#include "editor_Map.h"
#include "editor_Pos.h"

Map::Map(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& builder)
        : Gtk::Layout(cobject),
          m_builder(builder),
          button_id(1),
          action(0)
{
    add_events(Gdk::BUTTON_PRESS_MASK);
    signal_button_press_event().connect(
            sigc::mem_fun(*this,&Map::on_button_clicked));
    pallete.emplace_back("resources/images/right_worm.png");
    pallete.emplace_back("resources/images/Girder/girder_3.png");
}


bool Map::on_button_clicked(GdkEventButton *button_event) {
    if(action==0) {
        Gtk::Image new_image(pallete[button_id]);
        Pos pos(button_event->x,button_event->y);
        const Glib::RefPtr<Gdk::Pixbuf> &img = new_image.get_pixbuf();

        put(new_image, pos.getPrintableWidth(img->get_width()),
            pos.getPrintableHeigth(img->get_height()));
        new_image.show();
        objects.emplace_back(std::move(new_image),pos);
        Gtk::ScrolledWindow* map= nullptr;
        m_builder->get_widget("mapw",map);

    } else if(action==1){

        std::pair<Gtk::Image, Pos> &image = objects.back();
        const Glib::RefPtr<Gdk::Pixbuf> &img = image.first.get_pixbuf();

        image.second.updatePos(button_event->x,button_event->y);

        move(image.first,image.second.getPrintableWidth(img->get_width()),
             image.second.getPrintableHeigth(img->get_height()));

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
