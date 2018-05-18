
#include <gtkmm/builder.h>
#include "editor_Toolbox.h"
#include "editor_Map.h"

Toolbox::Toolbox(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& builder)
        : Gtk::Grid(cobject),
          m_builder(builder),
          btn_clean(nullptr),
          undo(nullptr),
          worm(nullptr),
          girder(nullptr),
          move(nullptr)

{
    builder->get_widget("btn_undo",undo);
    builder->get_widget("btn_clean",btn_clean);
    builder->get_widget("tbtn_worm",worm);
    worm->set_active(true);
    builder->get_widget("tbtn_grd",girder);
    builder->get_widget("btn_move",move);
    worm->signal_clicked().connect( sigc::bind<int>
                                           (sigc::mem_fun(*this,&Toolbox::on_button_clicked),WORM_BUTTON_ID));
    girder->signal_clicked().connect( sigc::bind<int>
                                             (sigc::mem_fun(*this, &Toolbox::on_button_clicked),
                                              GIRDER_BUTTON_ID ));


}

void Toolbox::link_map(Map *pMap) {
    map=pMap;
    undo->signal_clicked().connect( sigc::mem_fun(*map, &Map::undo) );
    btn_clean->signal_clicked().connect( sigc::mem_fun(*map, &Map::clean));
    move->signal_clicked().connect(
            sigc::mem_fun(*map, &Map::move_signal),WORM_BUTTON_ID);
}

void Toolbox::on_button_clicked(int id) {
    if(id ==WORM_BUTTON_ID) {
        if (worm->get_active()) {
            item_pressed = WORM_BUTTON_ID;
            girder->set_active(false);
            map->clicked_signal(WORM_BUTTON_ID);
        }
    } else {
        if (girder->get_active()) {
            item_pressed = GIRDER_BUTTON_ID;
            worm->set_active(false);
            map->clicked_signal(GIRDER_BUTTON_ID);
        }
    }
}
