
#include <gtkmm/builder.h>
#include "ToolBoxView.h"



ToolBoxView::ToolBoxView(BaseObjectType *cobject,
                         const Glib::RefPtr<Gtk::Builder> &builder)
        : Gtk::Grid(cobject),
          m_builder(builder) {
    builder->get_widget("btn_undo", erase);
    builder->get_widget("btn_clean", btn_clean);
    builder->get_widget("tbtn_worm", worm);
    worm->set_active(true);
    builder->get_widget("tbtn_grd", girder_3m);
    builder->get_widget("tbtn_grd6", girder_6m);
    builder->get_widget("btn_move", move);
    builder->get_widget("btn_turn_ccw", turnccw);
    builder->get_widget("btn_turn_cw", turncw);
    //turnccw->set_sensitive(false);
    //turncw->set_sensitive(false);


    worm->signal_clicked().connect(sigc::bind<int>
                                           (sigc::mem_fun(*this,
                                                          &ToolBoxView::on_button_clicked),
                                            WORM_BUTTON_ID));
    girder_3m->signal_clicked().connect(sigc::bind<int>
                                             (sigc::mem_fun(*this,
                                                            &ToolBoxView::on_button_clicked),
                                              GIRDER_3_BUTTON_ID));

    girder_6m->signal_clicked().connect(sigc::bind<int>
                                                (sigc::mem_fun(*this,
                                                               &ToolBoxView::on_button_clicked),
                                                 GIRDER_6_BUTTON_ID));
}

void ToolBoxView::linkController(std::shared_ptr<MapController> controller) {
    this->map_controller = std::move(controller);

    erase->signal_clicked().connect(
            sigc::mem_fun(*map_controller, &MapController::undo));

    btn_clean->signal_clicked().connect(
            sigc::mem_fun(*map_controller, &MapController::clean));

    move->signal_clicked().connect(
            sigc::mem_fun(*map_controller, &MapController::moveSignal));

    turnccw->signal_clicked().connect(
            sigc::mem_fun(*map_controller, &MapController::turnCCWSignal));

    turncw->signal_clicked().connect(
            sigc::mem_fun(*map_controller, &MapController::turnCWSignal));

}

void ToolBoxView::on_button_clicked(unsigned id) {
    if (id == WORM_BUTTON_ID) {
        if (worm->get_active()) {
            girder_3m->set_active(false);
            girder_6m->set_active(false);
            turnccw->set_sensitive(false);
            turncw->set_sensitive(false);
        }
    } else if (id == GIRDER_3_BUTTON_ID){
        if (girder_3m->get_active()) {
            worm->set_active(false);
            girder_6m->set_active(false);
            turnccw->set_sensitive(true);
            turncw->set_sensitive(true);
        }
    }else{
        girder_3m->set_active(false);
        worm->set_active(false);
        turnccw->set_sensitive(true);
        turncw->set_sensitive(true);
    }
    map_controller->itemSelectedSignal(id);
}
