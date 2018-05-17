
#ifndef WORMS_TOOLBOX_H
#define WORMS_TOOLBOX_H

#include <gtkmm/grid.h>
#include <gtkmm/button.h>
#include <gtkmm/layout.h>
#include "editor_Map.h"

class Toolbox : public Gtk::Grid {
private:
    Glib::RefPtr<Gtk::Builder> m_builder;
    Gtk::Button* btn_clean;
    Gtk::Button* undo;
    Map* map;

public:
    Toolbox(BaseObjectType *cobject, const Glib::RefPtr<Gtk::Builder> &builder);

    void link_map(Map *pMap);
};


#endif //WORMS_TOOLBOX_H
