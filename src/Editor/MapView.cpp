
#include <iostream>
#include <fstream>
#include "yaml-cpp/yaml.h"
#include "MapView.h"

MapView::MapView(BaseObjectType *cobject,
                 const Glib::RefPtr<Gtk::Builder> &builder)
        : Gtk::Layout(cobject),
          m_builder(builder) {
    add_events(Gdk::BUTTON_PRESS_MASK);
    signal_button_press_event().connect(
            sigc::mem_fun(*this, &MapView::on_button_clicked));
    pallete.emplace_back("resources/images/right_worm.png");
    for (int i = 0; i < 180; i = i + 10) {
        pallete.emplace_back(
                "resources/images/Girder/girder_3_" + std::to_string(i) +
                ".png");
    }
    for (int i = 0; i < 180; i = i + 10) {
        pallete.emplace_back(
                "resources/images/Girder/girder_6_" + std::to_string(i) +
                ".png");
    }
}


void MapView::add(unsigned int id, const double & x, const double & y, const int &angle) {
    Gtk::Image new_image(pallete[id - 1]);
    const Glib::RefPtr<Gdk::Pixbuf> &img = new_image.get_pixbuf();
    put(new_image, x - img->get_width() / 2, y - img->get_height() / 2);
    new_image.show();
    objects.push_back(std::move(new_image));
    if (angle>0)
        turnLast(angle);
}

void MapView::moveLast(const double &x, const double &y) {
    if (!objects.empty()) {
        Gtk::Image &actual_object = objects.back();
        move(actual_object, x - actual_object.get_width() / 2,
             y - actual_object.get_height() / 2);
        actual_object.show();
    }
}

void MapView::turnLast(const int &angle) {
    if (!objects.empty()) {
        Gtk::Image &image = objects.back();
        image.set(pallete[angle / 10 + 1]);
    }
}


bool MapView::on_button_clicked(GdkEventButton *button_event) {
    controller->mapClickedSignal(button_event);
    return true;
}

void MapView::undo() {
    if (!objects.empty())
        objects.pop_back();
}

void MapView::clean() {
    objects.clear();
}

void MapView::linkController(MapController *pController) {
    this->controller = pController;
}








