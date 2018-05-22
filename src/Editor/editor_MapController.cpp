
#include "editor_MapController.h"

#define ADD_CMD_ID 0
#define MOVE_CMD_ID 1
#define TURN_CMD_ID 2

MapController::MapController(const MapModel &model, Map &view) : model(
        model), view(view), actual_item_selected(1) ,actual_action_id(0) {}

void MapController::itemSelectedSignal(unsigned int id) {
    this->actual_item_selected=id;
}

void MapController::undo(){
    model.undo();
    view.undo();
}
void MapController::clean(){
    model.clean();
    view.clean();

}
void MapController::moveSignal(){
    this->actual_action_id=MOVE_CMD_ID;

}
void MapController::turnSignal(){
    this->actual_action_id=TURN_CMD_ID;

}
void MapController::saveSignal(){

}
void MapController::loadSignal(){

}

void MapController::mapClickedSignal(GdkEventButton *event_button) {
    if(actual_action_id==MOVE_CMD_ID){
        this->model.moveLast(event_button->x,event_button->y);
        this->view.moveLast(event_button->x,event_button->y);
    } else if (actual_action_id==TURN_CMD_ID){
        int new_angle = this->model.turnLast();
        this->view.turnLast(new_angle);
    } else{
        this->model.add(actual_item_selected,event_button->x,event_button->y);
        this->view.add(actual_item_selected,event_button->x,event_button->y);
    }
    actual_action_id=ADD_CMD_ID;
}


