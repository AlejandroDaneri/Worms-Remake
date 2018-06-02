
#ifndef WORMS_TOOLBOX_H
#define WORMS_TOOLBOX_H

#include <gtkmm/grid.h>
#include <gtkmm/button.h>
#include <gtkmm/layout.h>
#include <gtkmm/togglebutton.h>
#include <gtkmm/switch.h>
#include <gtkmm/hvbox.h>
#include "MapView.h"
#include "MapController.h"

#define WORM_BUTTON_ID 1
#define GIRDER_3_BUTTON_ID 3
#define GIRDER_6_BUTTON_ID 6

class MapController;

class ToolBoxView : public Gtk::Grid {
private:
    Gtk::Button *erase;
    MapController *map_controller;
    Gtk::ToggleButton *worm;
    Gtk::ToggleButton *girder_3m;
    Gtk::ToggleButton *girder_6m;
    Gtk::Button *move;

    Gtk::Button *turnccw;
    Gtk::Button *turncw;
    Gtk::Button *change_bg;
    Gtk::ToggleButton *mode;
    Gtk::Image* selected;
    bool processing;

public:
    ToolBoxView(BaseObjectType *cobject,
                const Glib::RefPtr<Gtk::Builder> &builder);

    void onNewObjectClicked(unsigned int id);

    void enableMovingItems();

    void linkController(MapController *controller);

    void disableMovingItems();

    void changeModeSignal();

    void leaveConsistent();

    void showSelected(int id);

    void hideSelected();

    void closeSelectionMode();

    void setMoveMode();
};


#endif //WORMS_TOOLBOX_H
