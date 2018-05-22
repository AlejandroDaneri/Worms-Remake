
#ifndef WORMS_MAPCONTROLLER_H
#define WORMS_MAPCONTROLLER_H


#include "editor_Map.h"
#include "editor_MapModel.h"

class Map;

class MapController {
    MapModel model;
    Map& view;
    unsigned int actual_item_selected;
    unsigned int actual_action_id;

public:
    MapController(const MapModel &model, Map &view);

    void itemSelectedSignal(unsigned int id);

    void undo();

    void clean();

    void moveSignal();

    void turnSignal();

    void saveSignal();

    void loadSignal();


    void mapClickedSignal(GdkEventButton *event_button);
};


#endif //WORMS_MAPCONTROLLER_H
