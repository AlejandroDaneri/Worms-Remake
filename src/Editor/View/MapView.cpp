
#include <Path.h>
#include <gtkmm/adjustment.h>
#include <gtkmm/scrolledwindow.h>
#include <glibmm/main.h>
#include "MapView.h"
#include "Math.h"
#include "ObjectSizes.h"

#define BACKGROUND_QUANTITY 8

MapView::MapView(BaseObjectType *cobject,
                 const Glib::RefPtr<Gtk::Builder> &builder)
        : Gtk::Layout(cobject),
          scroll_handler(*(Gtk::ScrolledWindow*)this->get_parent()), actual_background_index(0) {

    add_events(Gdk::BUTTON_PRESS_MASK);
    signal_button_press_event().connect(
            sigc::mem_fun(*this, &MapView::on_button_clicked));

    setInitialPosition();
    initializeBackground();
    initializeWormsImages();
    initializeGirderImages();
}

bool MapView::on_button_clicked(GdkEventButton *button_event) {
    controller->mapClickedSignal(button_event);
    return true;
}

void MapView::setInitialPosition() {
    guint width, height;
    get_size(width, height);
    ((Gtk::ScrolledWindow*) get_parent())->get_hadjustment()->set_value(width / 2);
    ((Gtk::ScrolledWindow*) get_parent())->get_vadjustment()->set_value(height);
}

void MapView::initializeBackground() {
    for (size_t i = 0; i < BACKGROUND_QUANTITY; i++){
		bg_paths.emplace_back(BACKGROUND_PATH + "background" + std::to_string(i) + ".jpg");
	}
    setBackground(bg_paths[actual_background_index]);
}

void MapView::initializeGirderImages(){
    std::vector<std::string> girder_3_imgs;
    std::vector<std::string> girder_6_imgs;

    for (int i = 0; i < 180; i = i + 10) {
        girder_3_imgs.emplace_back(
                IMAGES_PATH + "/Girder/girder_3_" + std::to_string(i) +
                ".png");
        girder_6_imgs.push_back(
                IMAGES_PATH + "/Girder/girder_6_" + std::to_string(i) +
                ".png");
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
		sigc::slot<bool> my_slot = sigc::bind(sigc::mem_fun(*this, &MapView::turn), id, angle, contained_objects.size()-1);
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
        
        int rotation = angle;
        if (rotation > 90){
			rotation = 180 - angle;
		}
        int height = SCALE_FACTOR * (Math::sinDegrees(rotation) * id + Math::cosDegrees(rotation) * girder_height);
        int width = SCALE_FACTOR * (Math::cosDegrees(rotation) * id + Math::sinDegrees(rotation) * girder_height);
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

void MapView::changeBackground() {
    background.clear();
    actual_background_index = (actual_background_index + 1) % bg_paths.size();
    setBackground(bg_paths[actual_background_index]);
}

void MapView::setBackground(const std::string &name) {
    Gtk::Image bg(name);
    int img_width = bg.get_pixbuf()->get_width();
    int img_height = bg.get_pixbuf()->get_height();
    guint window_width, window_height;
    this->get_size(window_width, window_height);
    for (size_t x = 0; x < window_width; x += img_width) {
        for (size_t y = 0; y < window_height; y += img_height) {
            Gtk::Image image(name);
            image.show();
            put(image, x, y);
            background.push_back(std::move(image));
        }
    }
    redrawMap();
}

void MapView::redrawMap() {
    for(Gtk::Image &object : contained_objects){
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

const std::string MapView::getBackgroundName() const {
    return "background"+std::to_string(actual_background_index)+".jpg";
}

void MapView::loadBackground(const std::string &name) {
    background.clear();
    setBackground(BACKGROUND_PATH+name);
}

