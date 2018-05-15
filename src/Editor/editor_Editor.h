
#ifndef PROJECT_MAPEDITOR_H
#define PROJECT_MAPEDITOR_H


#include <gtkmm/window.h>
#include <gtkmm/hvbox.h>
#include "editor_MapArea.h"
#include "editor_ToolBox.h"
#include "editor_WeaponsArea.h"

class Editor : public Gtk::Window {
private:
    Gtk::Notebook generalContainer;
    Gtk::HBox mapTab,wepTab;
    MapArea mapArea;
    WeaponsArea wepArea;
    ToolBox toolBox;
public:
protected:

    bool on_button_release_event(GdkEventButton *release_event) override;

public:
    Editor();
};


#endif //PROJECT_MAPEDITOR_H
