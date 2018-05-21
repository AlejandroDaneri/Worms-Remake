
#ifndef WORMS_EDITOR_H
#define WORMS_EDITOR_H


#include <gtkmm/window.h>
#include <gtkmm/scrolledwindow.h>
#include "editor_Map.h"
#include "editor_WeaponsBar.h"
#include "editor_Toolbox.h"

class Editor : public Gtk::Window {
    Glib::RefPtr<Gtk::Builder> m_builder;
    Gtk::ScrolledWindow* map_window;
    Map* map;
    Toolbox* toolbox;
    WeaponsBar* wepbar ;


public:
    Editor(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& builder);

};


#endif //WORMS_EDITOR_H
