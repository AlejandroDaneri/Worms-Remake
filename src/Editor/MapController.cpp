
#include <gtkmm/messagedialog.h>
#include <ViewPositionTransformer.h>
#include "MapController.h"
#include "InvalidMapError.h"

#define ADD_MODE_ID 0
#define MOVE_CMD_ID 1
#define SELECT_MODE_ID 2


MapController::MapController(Map model,
                             const Glib::RefPtr<Gtk::Builder> &builder)
        : model(std::move(model)), item_id_to_add(1),
          actual_mode(ADD_MODE_ID)
{
    builder->get_widget_derived("map", view);
    builder->get_widget_derived("toolbox", toolBox);
    view->linkController(this);
    toolBox->linkController(this);
}

void MapController::addModeSignal(unsigned int id) {
    this->actual_mode = ADD_MODE_ID;
    this->item_id_to_add = id;
}

void MapController::erase() {
    model.erase(actual_object_selected);
    view->erase(actual_object_selected);
    changeModeSignal();
    toolBox->disableMovingItems();
}

void MapController::clean() {
    model.clean();
    view->clean();
    toolBox->closeSelectionMode();
}

void MapController::moveSignal() {
    this->actual_mode = MOVE_CMD_ID;
}

void MapController::changeModeSignal() {
    this->actual_mode = (actual_mode==ADD_MODE_ID? SELECT_MODE_ID:ADD_MODE_ID);
    if (actual_mode==ADD_MODE_ID) toolBox->closeSelectionMode();
}

void MapController::turnCCWSignal() {
    if (model.isGirder(actual_object_selected)) {
        unsigned int id;
        int new_angle = this->model.turnCCWLast(actual_object_selected, id);
        this->view->turn(id, new_angle, actual_object_selected);
    }
}

void MapController::turnCWSignal() {
    if (model.isGirder(actual_object_selected)) {
        unsigned int id;
        int new_angle = this->model.turnCWLast(actual_object_selected, id);
        this->view->turn(id, new_angle, actual_object_selected);
    }
}

void MapController::mapClickedSignal(GdkEventButton *event_button) {
    if (actual_mode == MOVE_CMD_ID) {
        this->model.move(actual_object_selected, event_button->x,
                         event_button->y);
        this->view->move(actual_object_selected, event_button->x,
                         event_button->y);
    } else if (actual_mode == SELECT_MODE_ID) {
        this->actual_object_selected = view->select(event_button->x,
                                                    event_button->y);
        if (actual_object_selected > -1) {
            toolBox->enableMovingItems();
            toolBox->showSelected(model.getItemID(actual_object_selected));
        } else {
            toolBox->disableMovingItems();
            toolBox->hideSelected();
        }
        actual_mode = SELECT_MODE_ID; //cambio de estado del toolbox llama a add mode
    } else {
        this->model.add(item_id_to_add, event_button->x, event_button->y);
        this->view->add(item_id_to_add, event_button->x, event_button->y);
    }
}

void MapController::getObjects(std::vector<std::vector<double>> &worms,
                               std::vector<std::vector<double>> &girders) const {
    model.getObjects(worms, girders);
    if (worms.empty()){
        throw InvalidMapError("El mapa actual no contiene worms");
    }
    if (girders.empty()){
        throw InvalidMapError("El mapa actual no contiene vigas");
    }

    ViewPositionTransformer transformer(*view);
    for (std::vector<double> &worm : worms){
        Position position(worm[0],worm[1]);
        Position new_pos = transformer.transformToPosition(position);
        worm[0] = new_pos.getX();
        worm[1] = new_pos.getY();
    }
    for (std::vector<double> &girder : girders){
        Position position(girder[1],girder[2]);
        Position new_pos = transformer.transformToPosition(position);
        girder[1] = new_pos.getX();
        girder[2] = new_pos.getY();
    }
}

void MapController::loadObjects(std::vector<std::vector<double>> &worms,
                                std::vector<std::vector<double>> &girders) {
    clean();
    ViewPositionTransformer transformer(*view);
    for (std::vector<double> &worm:worms) {
        Position position(worm[0],worm[1]);
        Position new_pos = transformer.transformToScreen(position);
        worm[0] = new_pos.getX();
        worm[1] = new_pos.getY();
        this->model.add(1, worm[0], worm[1]);
        this->view->add(1, worm[0], worm[1]);
    }
    for (std::vector<double> &girder:girders) {
        Position position(girder[1],girder[2]);
        Position new_pos = transformer.transformToScreen(position);
        girder[1] = new_pos.getX();
        girder[2] = new_pos.getY();
        this->model.add(girder[0], girder[1], girder[2], girder[3]);
        this->view->add(girder[0], girder[1], girder[2], girder[3]);
    }
}

void MapController::changeBackground() {
    this->view->changeBackground();
}
