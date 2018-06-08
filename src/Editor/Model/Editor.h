
#ifndef WORMS_EDITOR_H
#define WORMS_EDITOR_H

#include <gtkmm/builder.h>
#include <gtkmm/window.h>
#include <gtkmm/scrolledwindow.h>
#include <gtkmm/spinbutton.h>
#include "MapView.h"
#include "ToolBoxView.h"
#include "UsablesController.h"
#include "FileBoxController.h"
#include "FileBoxView.h"

class Editor : public Gtk::Window {
    Gtk::ScrolledWindow *map_window;
    Map map_model;
    UsablesController usables_controller;
    FileBoxView *filebox;

public:
    Editor(BaseObjectType *cobject, const Glib::RefPtr<Gtk::Builder> &builder);

};


#endif //WORMS_EDITOR_H
