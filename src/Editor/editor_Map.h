
#ifndef WORMS_MAP_H
#define WORMS_MAP_H

#include <gtkmm/builder.h>
#include <gtkmm/layout.h>
#include <gtkmm/image.h>
#include "editor_MapController.h"
#include "editor_ObjectView.h"

class MapController;

class Map : public Gtk::Layout {
private:
    Glib::RefPtr<Gtk::Builder> m_builder;
    std::vector<Gtk::Image> objects;
    std::vector<std::string> pallete;
    MapController *controller;

public:
    Map(BaseObjectType *cobject, const Glib::RefPtr<Gtk::Builder> &builder);

    bool on_button_clicked(GdkEventButton *button_event);

    void undo();

    void clean();

    void save_signal();

    void load_signal();

    void linkController(MapController *pController);

    void add(unsigned int &id, double &x, double &y);

    void moveLast(double &x, double &y);

    void turnLast(int &angle);
};


#endif //WORMS_MAP_H
