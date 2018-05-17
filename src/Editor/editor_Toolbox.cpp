
#include <gtkmm/builder.h>
#include "editor_Toolbox.h"
#include "editor_Map.h"

Toolbox::Toolbox(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& builder)
        : Gtk::Grid(cobject),
          m_builder(builder),
          btn_clean(nullptr),
          undo(nullptr)

{
    builder->get_widget("btn_undo",undo);
    builder->get_widget("btn_clean",btn_clean);

}

void Toolbox::link_map(Map *pMap) {
    map=pMap;
    undo->signal_clicked().connect( sigc::mem_fun(*map, &Map::undo) );
    btn_clean->signal_clicked().connect( sigc::mem_fun(*map, &Map::clean));
}


