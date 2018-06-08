
#ifndef WORMS_MAPCONTROLLER_H
#define WORMS_MAPCONTROLLER_H

#include "MapView.h"
#include "Map.h"
#include "ToolBoxView.h"
class MapView;
class ToolBoxView;

// Clase que se encarga de comunicar la vista con el modelo, y a su vez, se
// comunica con el resto del programa
class MapController {
    Map model;
    MapView *view;
    ToolBoxView *toolBox;
    unsigned int item_id_to_add;
    unsigned int actual_mode;
    int index_object_selected;

    void turn(const int &rotation);
public:
    MapController(Map model, const Glib::RefPtr<Gtk::Builder> &builder);

    void addModeSignal(const unsigned int &id);

    void eraseSignal();

    void newMapSignal();

    void moveSignal();

    void turnCCWSignal();

    void mapClickedSignal(GdkEventButton *event_button);

    void getObjects(std::vector<std::vector<double>> &worms,
                    std::vector<std::vector<double>> &girders) const;

    void loadObjects(std::vector<std::vector<double>> &worms,
                     std::vector<std::vector<double>> &girders);

    void turnCWSignal();

    void changeBackgroundSignal() const;

    void changeModeSignal();

    const std::string getBackgroundName() const;

    void loadBackground(const std::string &background);
};


#endif //WORMS_MAPCONTROLLER_H
