
#ifndef PROJECT_MAPEDITOR_H
#define PROJECT_MAPEDITOR_H


#include <gtkmm/window.h>
#include <gtkmm/hvbox.h>
#include "editor_MapArea.h"
#include "editor_ToolBox.h"

class MapEditor : public Gtk::Window {
private:
    Gtk::HBox parent;
    MapArea mapArea;
    ToolBox toolBox;
public:
    MapEditor();
};


#endif //PROJECT_MAPEDITOR_H
