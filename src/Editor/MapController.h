
#ifndef WORMS_MAPCONTROLLER_H
#define WORMS_MAPCONTROLLER_H


#include "MapView.h"
#include "Map.h"

class MapView;

class MapController {
    Map model;
    MapView &view;
    unsigned int actual_item_selected;
    unsigned int actual_action_id;

public:
    MapController(const Map &model, MapView &view);

    void itemSelectedSignal(unsigned int id);

    void undo();

    void clean();

    void moveSignal();

    void turnSignal();

    void saveSignal();

    void loadSignal();

    void mapClickedSignal(GdkEventButton *event_button);

    void getObjects(std::vector<std::vector<double>> &worms,
                    std::vector<std::vector<double>> &girders) const;
};


#endif //WORMS_MAPCONTROLLER_H
