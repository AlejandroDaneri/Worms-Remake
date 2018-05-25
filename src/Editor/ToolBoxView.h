
#ifndef WORMS_TOOLBOX_H
#define WORMS_TOOLBOX_H

#include <gtkmm/grid.h>
#include <gtkmm/button.h>
#include <gtkmm/layout.h>
#include <gtkmm/togglebutton.h>
#include "MapView.h"
#include "MapController.h"


#define WORM_BUTTON_ID 1
#define GIRDER_3_BUTTON_ID 3
#define GIRDER_6_BUTTON_ID 6

class ToolBoxView : public Gtk::Grid {
private:
    Glib::RefPtr<Gtk::Builder> m_builder;
    Gtk::Button *btn_clean;
    Gtk::Button *erase; //pasar a toggle
    std::shared_ptr<MapController> map_controller;
    Gtk::ToggleButton *worm;
    Gtk::ToggleButton *girder_3m;
    Gtk::ToggleButton *girder_6m;
    Gtk::Button *move;// pasar a toggle

    Gtk::Button *turnccw;
    Gtk::Button *turncw;

public:
    ToolBoxView(BaseObjectType *cobject,
                const Glib::RefPtr<Gtk::Builder> &builder);

    void linkController(std::shared_ptr<MapController> controller);

    void on_button_clicked(unsigned int id);

};


#endif //WORMS_TOOLBOX_H
