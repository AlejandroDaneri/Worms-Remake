
#include <iostream>
#include <fstream>
#include <ObjectSizes.h>
#include <Path.h>
#include <gtkmm/adjustment.h>
#include <gtkmm/scrolledwindow.h>
#include "yaml-cpp/yaml.h"
#include "MapView.h"

#define BACKGROUND_QUANTITY 8

MapView::MapView(BaseObjectType *cobject,
                 const Glib::RefPtr<Gtk::Builder> &builder)
        : Gtk::Layout(cobject),
          actual_bg(0) {

    guint width, height;
    this->get_size(width, height);
    ((Gtk::ScrolledWindow*)this->get_parent())->get_hadjustment()->set_value(width / 2);
	((Gtk::ScrolledWindow*)this->get_parent())->get_vadjustment()->set_value(height);

	for (size_t i = 1; i <= BACKGROUND_QUANTITY; i++){
		bg_paths.emplace_back(BACKGROUND_PATH + "background" + std::to_string(i) + ".jpg");
	}
    setBackground(bg_paths[actual_bg]);

    add_events(Gdk::BUTTON_PRESS_MASK);
    signal_button_press_event().connect(
            sigc::mem_fun(*this, &MapView::on_button_clicked));

    std::vector<std::string> worms_imgs;
    worms_imgs.emplace_back(IMAGES_PATH + "/right_worm.png");
    worms_imgs.emplace_back(IMAGES_PATH + "/left_worm.png");
    objects_pallete.push_back(worms_imgs);

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


bool MapView::on_button_clicked(GdkEventButton *button_event) {
    controller->mapClickedSignal(button_event);
    return true;
}

void MapView::add(const unsigned int &id, const double &x, const double &y,
                  const int &angle) {
    Gtk::Image new_image(objects_pallete[id - id / 2 - 1][0]);
    const Glib::RefPtr<Gdk::Pixbuf> &img = new_image.get_pixbuf();
    int width = img->get_width();
    int height = img->get_height();
    double x_bound = x - width / 2;
    double y_bound = y - height / 2;

    //if(isIsolated(x_bound,y_bound,id)){ //verifica que no haya colisiones
    put(new_image, x_bound, y_bound);
    new_image.show();
    objects.push_back(std::move(new_image));
    if (angle > 0)
        turn(id, angle, objects.size()-1);
    //}

}

void MapView::move(const int &index, const double &x, const double &y) {
    if (!objects.empty()) {
        Gtk::Image &actual_object = objects[index];
        Gtk::Layout::move(actual_object, x - actual_object.get_width() / 2,
                          y - actual_object.get_height() / 2);
        actual_object.show();
    }
}

void MapView::turn(const unsigned int &id, const int &angle, const int &index) {
    if (!objects.empty()) {
        Gtk::Image &image = objects[index];
        image.set(objects_pallete[id - id / 2 - 1][angle / 10]);
    }
}

void MapView::undo(const int &index) {
    if (!objects.empty()) {
        objects[index].hide();
        objects.erase(objects.begin() + index);
    }
}

void MapView::clean() {
    objects.clear();
}

void MapView::linkController(MapController *pController) {
    this->controller = pController;
}

void MapView::changeBackground() {
    background.clear();
    actual_bg = (actual_bg + 1) % bg_paths.size();
    setBackground(bg_paths[actual_bg]);
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
    redraw_map();
}

void MapView::redraw_map() {
    for(Gtk::Image &object : objects){
        const Gtk::Allocation &alloc = object.get_allocation();
        remove(object);
        put(object,alloc.get_x(),alloc.get_y());
    }
    this->water.show(*this);
}

int MapView::select(const double &x, const double &y) {
    Gdk::Rectangle new_object(x, y, 1, 1);
    bool collision = false;
    for (size_t i = 0; (i < objects.size()) && (!collision); i++) {
        collision = objects[i].intersect(new_object);
        if (collision) {
            this->actual_selected = i;
        }
    }
    return collision ? actual_selected:-1;
}

bool
MapView::isIsolated(const double &x, double y, const unsigned int &id) {
    int width, height;
    if (id == 1) {
        height = width = WORM_IMAGE_WIDTH;
    } else {
        y += 78; // espacio en blanco que tiene la imagen, 0 grados
        height = girder_height * SCALE_FACTOR;
        width = 180 * ((id - 1) / 2); //180 es el largo
    }
    std::cout << x << "  " << y << std::endl;
    Gdk::Rectangle new_object(x, y, width, height);
    bool isolated = true;
    for (size_t i = 0; (i < objects.size()) && (isolated); i++) {
        const Gtk::Allocation &asd = objects.back().get_allocation();
        int h = asd.get_height();
        int w = asd.get_width();
        if (h > w);
        isolated = !objects[i].intersect(new_object);
    }
    return isolated;
}

