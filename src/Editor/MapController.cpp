
#include "MapController.h"

#define ADD_CMD_ID 0
#define MOVE_CMD_ID 1


MapController::MapController(const Map &model, MapView &view) : model(
        model), view(view), actual_item_selected(1), actual_action_id(0) {
    view.linkController(this);
}

void MapController::itemSelectedSignal(unsigned int id) {
    this->actual_item_selected = id;
}

void MapController::undo() {
    model.undo();
    view.undo();
}

void MapController::clean() {
    model.clean();
    view.clean();

}

void MapController::moveSignal() {
    this->actual_action_id = MOVE_CMD_ID;
}

void MapController::turnCCWSignal() {
    if (model.lastIsGirder()) {
        int new_angle = this->model.turnCCWLast();
        this->view.turnLast(last_item_added, new_angle);
    }
}

void MapController::turnCWSignal() {
    if (model.lastIsGirder()) {
        int new_angle = this->model.turnCWLast();
        this->view.turnLast(last_item_added, new_angle);
    }
}

void MapController::mapClickedSignal(GdkEventButton *event_button) {
    if (actual_action_id == MOVE_CMD_ID) {
        this->model.moveLast(event_button->x, event_button->y);
        this->view.moveLast(event_button->x, event_button->y);
        actual_action_id = ADD_CMD_ID;
    } else {
        last_item_added = actual_item_selected;
        this->model.add(actual_item_selected, event_button->x, event_button->y);
        this->view.add(actual_item_selected, event_button->x, event_button->y);
    }
}

void MapController::getObjects(std::vector<std::vector<double>> &worms,
                               std::vector<std::vector<double>> &girders) const {
    model.getObjects(worms, girders);
}

void MapController::loadObjects(std::vector<std::vector<double>> &worms,
                                std::vector<std::vector<double>> &girders) {
    clean();
    for (const auto &worm:worms) {
        this->model.add(1, worm[0], worm[1]);
        this->view.add(1, worm[0], worm[1]);
    }
    for (const auto &girder:girders) {
        this->model.add(girder[0], girder[1], girder[2], girder[3]);
        this->view.add(girder[0], girder[1], girder[2], girder[3]);
    }
}

void MapController::changeBackground() {
    this->view.changeBackground();
}


