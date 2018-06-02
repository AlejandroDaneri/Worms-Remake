
#ifndef WORMS_MAP_H
#define WORMS_MAP_H

#include <gtkmm/builder.h>
#include <gtkmm/layout.h>
#include <gtkmm/image.h>
#include "Controllers/MapController.h"
#include "Water.h"
#include "ScrollHandler.h"

class MapController;

class MapView : public Gtk::Layout {
private:
    std::vector<Gtk::Image> objects;
    std::vector<std::vector<std::string>> objects_pallete;
    MapController *controller;
    std::vector<std::string> bg_paths;
    std::vector<Gtk::Image> background;
    Water water;
    ScrollHandler scroll_handler;

    int actual_bg;
    size_t actual_selected;

    void initializeWormsImages();

    void initializeGirderImages();

    void setBackground(const std::string &name);

    void initializeBackground();

    void setInitialPosition();

public:
    MapView(BaseObjectType *cobject, const Glib::RefPtr<Gtk::Builder> &builder);

    bool on_button_clicked(GdkEventButton *button_event);

    void erase(const int &index);

    void clean();

    void linkController(MapController *map_controller);

    void add(const unsigned int &id, const double &x, const double &y,
             const int &angle = 0);

    void turn(const unsigned int &id, const int &angle, const int &index);

    void changeBackground();

    int select(const double &x, const double &y);

    void move(const int& index, const double &x, const double &y);

    void redrawMap();

    const std::string getBackgroundName() const;

    void loadBackground(const std::string &name);

};

#endif //WORMS_MAP_H
