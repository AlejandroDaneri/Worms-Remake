
#ifndef WORMS_MAP_H
#define WORMS_MAP_H

#include <gtkmm/builder.h>
#include <gtkmm/layout.h>
#include <gtkmm/image.h>
#include "MapController.h"


class MapController;

class MapView : public Gtk::Layout {
private:
    std::vector<Gtk::Image> objects;
    std::vector<std::vector<std::string>> objects_pallete;
    MapController *controller;
    std::vector<std::string> bg_paths;
    std::vector<Gtk::Image> background;

    int actual_bg;
    size_t actual_selected;

    //bool isIsolated(const double &x, const double &y, const unsigned int &id);
    void setBackground(const std::string &name);

public:
    MapView(BaseObjectType *cobject, const Glib::RefPtr<Gtk::Builder> &builder);

    bool on_button_clicked(GdkEventButton *button_event);

    void undo(const int &index);

    void clean();

    void linkController(MapController *pController);

    void add(const unsigned int &id, const double &x, const double &y,
             const int &angle = 0);

    void turn(const unsigned int &id, const int &angle, const int &index);

    void changeBackground();

    int select(const double &x, const double &y);

    bool isIsolated(const double &x, double y, const unsigned int &id);

    void move(const int& index, const double &x, const double &y);
};


#endif //WORMS_MAP_H
