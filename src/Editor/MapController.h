
#ifndef WORMS_MAPCONTROLLER_H
#define WORMS_MAPCONTROLLER_H


#include "MapView.h"
#include "Map.h"
#include "ToolBoxView.h"

class MapView;

class ToolBoxView;

class MapController {
    Map model;
    MapView *view;
    ToolBoxView *toolBox;
    unsigned int actual_item_selected;
    unsigned int actual_mode;
    int actual_object_selected;


public:
    MapController(Map model, const Glib::RefPtr<Gtk::Builder> &builder);

    void addModeSignal(unsigned int id);

    void undo();

    void clean();

    void moveSignal();

    void turnCCWSignal();

    void mapClickedSignal(GdkEventButton *event_button);

    void getObjects(std::vector<std::vector<double>> &worms,
                    std::vector<std::vector<double>> &girders) const;

    void loadObjects(std::vector<std::vector<double>> &worms,
                     std::vector<std::vector<double>> &girders);

    void turnCWSignal();

    void changeBackground();

    void changeModeSignal();
};


#endif //WORMS_MAPCONTROLLER_H
