
#include <Path.h>
#include <gtkmm/adjustment.h>
#include <gtkmm/scrolledwindow.h>
#include <glibmm/main.h>
#include <vector>
#include <string>
#include "MapView.h"
#include "GirderSize.h"

const std::string DEFAULT_BACKGROUND("default_background.png");

MapView::MapView(BaseObjectType *cobject,
                 const Glib::RefPtr<Gtk::Builder> &builder)
        : Gtk::Layout(cobject),
          scroll_handler(*(Gtk::ScrolledWindow*)this->get_parent()){
    add_events(Gdk::BUTTON_PRESS_MASK);
    signal_button_press_event().connect(
            sigc::mem_fun(*this, &MapView::onButtonClicked));

    setInitialPosition();
    changeBackground(BACKGROUND_PATH + DEFAULT_BACKGROUND);
    initializeWormsImages();
    initializeGirderImages();
}

bool MapView::onButtonClicked(GdkEventButton *button_event) {
    controller->mapClickedSignal(button_event);
    return true;
}

void MapView::setInitialPosition() {
    guint w, h;
    get_size(w, h);
    ((Gtk::ScrolledWindow*) get_parent())->get_hadjustment()->set_value(w / 2);
    ((Gtk::ScrolledWindow*) get_parent())->get_vadjustment()->set_value(h);
}

void MapView::initializeGirderImages(){
    std::vector<std::string> girder_3_imgs;
    std::vector<std::string> girder_6_imgs;

    for (int i = 0; i < 180; i = i + 10) {
        girder_3_imgs.emplace_back(
                GIRDER_PATH + "3_" + std::to_string(i) + ".png");
        girder_6_imgs.push_back(
                GIRDER_PATH + "6_" + std::to_string(i) + ".png");
    }
    objects_pallete.push_back(girder_3_imgs);
    objects_pallete.push_back(girder_6_imgs);
}

void MapView::initializeWormsImages()  {
    std::vector<std::string> worms_imgs;
    worms_imgs.emplace_back(IMAGES_PATH + "/right_worm.png");
    objects_pallete.push_back(worms_imgs);
}

void MapView::add(const unsigned int &id, const double &x, const double &y,
                  const int &angle) {
    Gtk::Image new_image(objects_pallete[id - id / 2 - 1][0]);
    const Glib::RefPtr<Gdk::Pixbuf> &img = new_image.get_pixbuf();
    int width = img->get_width();
    int height = img->get_height();
    double x_bound = x - width / 2;
    double y_bound = y - height / 2;

    put(new_image, x_bound, y_bound);
    new_image.show();
    contained_objects.push_back(std::move(new_image));
    if (angle > 0){
		sigc::slot<bool> my_slot = sigc::bind(sigc::mem_fun(
            *this, &MapView::turn), id, angle, contained_objects.size() - 1);
		Glib::signal_idle().connect(my_slot);
	}
}

void MapView::move(const int &index, const double &x, const double &y) {
    if (!contained_objects.empty()) {
        Gtk::Image &actual_object = contained_objects[index];
        Gtk::Layout::move(actual_object, x - actual_object.get_width() / 2,
                          y - actual_object.get_height() / 2);
        actual_object.show();
    }
}

bool MapView::turn(const unsigned int &id, const int &angle, const int &index) {
    if (!contained_objects.empty()) {
        Gtk::Image &image = contained_objects[index];
        float x = child_property_x(image) + image.get_width() / 2;
        float y = child_property_y(image) + image.get_height() / 2;
        image.set(objects_pallete[id - id / 2 - 1][angle / 10]);

        int height = GirderSize::getGirderHeightPixels(id, angle);
        int width = GirderSize::getGirderWidthPixels(id, angle);
        Gtk::Layout::move(image, x - width / 2, y - height / 2);
    }
    return false;
}

void MapView::erase(const int &index) {
    if (!contained_objects.empty()) {
        contained_objects[index].hide();
        contained_objects.erase(contained_objects.begin() + index);
    }
}

void MapView::clean() {
    contained_objects.clear();
}

void MapView::bindController(MapController *map_controller) {
    this->controller = map_controller;
}

void MapView::changeBackground(const std::string &path) {
    Gtk::Image bg(path);
    loadBackground(bg.get_pixbuf());
}

void MapView::redrawMap() {
    for (Gtk::Image &object : contained_objects){
        const Gtk::Allocation &alloc = object.get_allocation();
        remove(object);
        put(object,alloc.get_x(),alloc.get_y());
    }
    this->water.show(*this);
}

int MapView::select(const double &x, const double &y) {
    Gdk::Rectangle new_object(x, y, 1, 1);
    for (ssize_t i = contained_objects.size() - 1; i >= 0; i--) {
        bool collision = contained_objects[i].intersect(new_object);
        if (collision) {
            return i;
        }
    }
    return -1;
}

Glib::RefPtr<const Gdk::Pixbuf> MapView::getBackground() const{
    return this->background[0].get_pixbuf();
}

void MapView::loadBackground(Glib::RefPtr<Gdk::Pixbuf> pixbuf) {
	background.clear();
    int img_width = pixbuf->get_width();
    int img_height = pixbuf->get_height();
    guint window_width, window_height;
    this->get_size(window_width, window_height);
    for (size_t x = 0; x < window_width; x += img_width) {
        for (size_t y = 0; y < window_height; y += img_height) {
            Gtk::Image image(pixbuf);
            image.show();
            put(image, x, y);
            background.push_back(std::move(image));
        }
    }
    redrawMap();
}

