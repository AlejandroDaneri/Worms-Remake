
#ifndef PROJECT_MAPEDITOR_H
#define PROJECT_MAPEDITOR_H


#include <gtkmm/window.h>
#include <gtkmm/hvbox.h>
#include "editor_MapArea.h"
#include "editor_ToolBox.h"
#include "WeaponsArea.h"

class MapEditor : public Gtk::Window {
private:
    Gtk::Notebook grandpa;
    Gtk::HBox mapTab,wepTab;
    MapArea mapArea;
    WeaponsArea wepArea;
    ToolBox toolBox;
public:
protected:

    bool on_button_release_event(GdkEventButton *release_event) override;

public:
    MapEditor();
};


#endif //PROJECT_MAPEDITOR_H
