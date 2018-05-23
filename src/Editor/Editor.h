
#ifndef WORMS_EDITOR_H
#define WORMS_EDITOR_H

#include <gtkmm/builder.h>
#include <gtkmm/window.h>
#include <gtkmm/scrolledwindow.h>
#include "MapView.h"
#include "ToolBoxView.h"
#include "WeaponsListController.h"

class Editor : public Gtk::Window {
    Glib::RefPtr<Gtk::Builder> m_builder;
    Gtk::ScrolledWindow *map_window;
    MapView *map;
    ToolBoxView *toolbox;
    Map map_model;

    Gtk::Button *weps_reset_button;
    WeaponListt weplist;
    WeaponsListController weps_list_controller;

public:
    Editor(BaseObjectType *cobject, const Glib::RefPtr<Gtk::Builder> &builder);

};


#endif //WORMS_EDITOR_H
