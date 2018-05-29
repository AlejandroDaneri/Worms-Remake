
#include <gtkmm/builder.h>
#include "ToolBoxView.h"


ToolBoxView::ToolBoxView(BaseObjectType *cobject,
                         const Glib::RefPtr<Gtk::Builder> &builder)
        : Gtk::Grid(cobject) {
    running=false;
    builder->get_widget("btn_undo", erase);
    Gtk::manage(erase);
    builder->get_widget("tbtn_worm", worm);
    Gtk::manage(worm);
    worm->set_active(true);
    builder->get_widget("tbtn_grd", girder_3m);
    Gtk::manage(girder_3m);
    builder->get_widget("tbtn_grd6", girder_6m);
    Gtk::manage(girder_6m);
    builder->get_widget("btn_move", move);
    Gtk::manage(move);
    builder->get_widget("btn_turn_ccw", turnccw);
    Gtk::manage(turnccw);
    builder->get_widget("btn_turn_cw", turncw);
    Gtk::manage(turncw);
    builder->get_widget("btn_bg", change_bg);
    Gtk::manage(change_bg);
    builder->get_widget("btn_mode", mode);
    Gtk::manage(mode);

    worm->signal_clicked().connect(sigc::bind<int>
                                           (sigc::mem_fun(*this,
                                                          &ToolBoxView::onNewObjectClicked),
                                            WORM_BUTTON_ID));
    girder_3m->signal_clicked().connect(sigc::bind<int>
                                                (sigc::mem_fun(*this,
                                                               &ToolBoxView::onNewObjectClicked),
                                                 GIRDER_3_BUTTON_ID));

    girder_6m->signal_clicked().connect(sigc::bind<int>
                                                (sigc::mem_fun(*this,
                                                               &ToolBoxView::onNewObjectClicked),
                                                 GIRDER_6_BUTTON_ID));
}

void ToolBoxView::linkController(MapController *controller) {
    this->map_controller = controller;

    erase->signal_clicked().connect(
            sigc::mem_fun(*map_controller, &MapController::undo));

    move->signal_clicked().connect(
            sigc::mem_fun(*map_controller, &MapController::moveSignal));

    turnccw->signal_clicked().connect(
            sigc::mem_fun(*map_controller, &MapController::turnCCWSignal));

    turncw->signal_clicked().connect(
            sigc::mem_fun(*map_controller, &MapController::turnCWSignal));

    change_bg->signal_clicked().connect(
            sigc::mem_fun(*map_controller, &MapController::changeBackground));

    mode->signal_toggled().connect(
            sigc::mem_fun(*this, &ToolBoxView::changeModeSignal));
}

void ToolBoxView::onNewObjectClicked(unsigned id) {
    if (!running) {
        running=true;
        if (id == WORM_BUTTON_ID) {
            if (worm->get_active()) {
                girder_3m->set_active(false);
                girder_6m->set_active(false);
            }
        } else if (id == GIRDER_3_BUTTON_ID) {
            if (girder_3m->get_active()) {
                worm->set_active(false);
                girder_6m->set_active(false);
            }
        } else {
            girder_3m->set_active(false);
            worm->set_active(false);
        }
        disableMovingItems();
        mode->set_active(false);
        map_controller->addModeSignal(id);
        leaveConsistent();
        running=false;
    }
}

void ToolBoxView::enableMovingItems() {
    turncw->set_sensitive(true);
    turnccw->set_sensitive(true);
    move->set_sensitive(true);
    erase->set_sensitive(true);
}

void ToolBoxView::disableMovingItems() {
    turncw->set_sensitive(false);
    turnccw->set_sensitive(false);
    move->set_sensitive(false);
    erase->set_sensitive(false);
}

void ToolBoxView::changeModeSignal() {
    worm->set_sensitive(!mode->get_active());
    girder_3m->set_sensitive(!mode->get_active());
    girder_6m->set_sensitive(!mode->get_active());
    if(!mode->get_active()){
        disableMovingItems();
    }
    map_controller->changeModeSignal();

}

void ToolBoxView::leaveConsistent() {
    if (!worm->get_active() && !girder_6m->get_active() && !girder_3m->get_active()){
        running=true;
        worm->set_active(true);
        map_controller->addModeSignal(WORM_BUTTON_ID);
    }
}
