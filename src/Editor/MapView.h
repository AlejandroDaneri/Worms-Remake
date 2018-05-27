
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
    std::vector<std::vector<std::string>> pallete;
    MapController *controller;

    std::vector<Gtk::Image> back;

    int actual_bg;
    void setBackground(std::string name);
    std::vector<std::string> bg_paths;

    //bool isIsolated(const double &x, const double &y, const unsigned int &id);

public:
    MapView(BaseObjectType *cobject, const Glib::RefPtr<Gtk::Builder> &builder);

    bool on_button_clicked(GdkEventButton *button_event);

    void undo();

    void clean();

    void linkController(MapController *pController);

    void add(unsigned int id, const double &x, const double &y,
             const int &angle = 0);

    void moveLast(const double &x, const double &y);

    void turn(unsigned int id, int angle, int index);

    void changeBackground();

    int select(const double &x, const double &y);
    bool isIsolated(const double &x, double y, const unsigned int &id);

    size_t actual_selected;

    void move(const int index, const double &x, const double &y);
};


#endif //WORMS_MAP_H
