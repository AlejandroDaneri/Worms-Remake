
#ifndef WORMS_TOOLBOX_H
#define WORMS_TOOLBOX_H

#include <gtkmm/grid.h>
#include <gtkmm/button.h>
#include <gtkmm/layout.h>
#include <gtkmm/togglebutton.h>
#include "editor_Map.h"


#define WORM_BUTTON_ID 1
#define GIRDER_BUTTON_ID 2

class Toolbox : public Gtk::Grid {
private:
    Glib::RefPtr<Gtk::Builder> m_builder;
    Gtk::Button* btn_clean;
    Gtk::Button* erase; //pasar a toggle
    Map* map;
    Gtk::ToggleButton* worm;
    Gtk::ToggleButton* girder;
    Gtk::Button* move;// pasar a toggle
    bool item_pressed;
    Gtk::Button* turn;
    Gtk::Button* save;

public:
    Toolbox(BaseObjectType *cobject, const Glib::RefPtr<Gtk::Builder> &builder);

    void link_map(Map *pMap);
    void on_button_clicked(int id) ;

};


#endif //WORMS_TOOLBOX_H
