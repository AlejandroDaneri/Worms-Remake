#include "WorldView.h"
#include <gtkmm/adjustment.h>
#include "ViewPositionTransformer.h"
#include "Player.h"
#include "Math.h"
#include "Path.h"
#include "ObjectSizes.h"

WorldView::WorldView() {
	this->world.set_size(map_width, map_height);
	this->window.add_events(Gdk::BUTTON_PRESS_MASK);
	this->window.add(this->world);

	this->window.get_hadjustment()->set_value(map_width / 2);
	this->window.get_vadjustment()->set_value(map_height);

	/////////////////////////// Cambiar a que se reciba por parametro
	std::string background_name(BACKGROUND_PATH + "background2.png");

	Gtk::Image aux(background_name);
	int img_width = aux.get_pixbuf()->get_width();
	int img_height = aux.get_pixbuf()->get_height();
	for (size_t x = 0; x < map_width; x += img_width) {
		for (size_t y = 0; y < map_height; y += img_height) {
			Gtk::Image background_image(background_name);
			background_image.show();
			this->world.put(background_image, x, y);
			this->background.push_back(std::move(background_image));
		}
	}
	this->water.show(this->world);
}

WorldView::~WorldView() {}

void WorldView::moveElement(Gtk::Widget& element, const Position& position, float width, float height, bool focus){
	Position newPosition = ViewPositionTransformer(this->world).transformToScreenAndMove(position, width, height);
	this->world.move(element, newPosition.getX(), newPosition.getY());
	if (focus){
		this->setFocus(element);
	}
}

void WorldView::moveScope(Gtk::Widget& scope, Gtk::Widget& worm, int angle) {
	float pos_x = this->world.child_property_x(worm).get_value();
	float pos_y = this->world.child_property_y(worm).get_value();
	pos_x += 50 * Math::cosDegrees(angle);
	pos_y -= 50 * Math::sinDegrees(angle);
	pos_x -= worm.get_width() / 2; // Para que quede referenciado a la mitad de la imagen
	this->world.move(scope, pos_x, pos_y);
}

void WorldView::removeElement(Gtk::Widget& element){
	this->world.remove(element);
}

void WorldView::addElement(Gtk::Widget& element, const Position& position, float width, float height, bool focus){
	Position newPosition = ViewPositionTransformer(this->world).transformToScreenAndMove(position, width, height);
	this->world.put(element, newPosition.getX(), newPosition.getY());
	element.show_all();
	if (focus){
		this->setFocus(element);
	}
}

Gtk::ScrolledWindow& WorldView::getWindow(){
	return this->window;
}

Gtk::Layout& WorldView::getLayout(){
	return this->world;
}

void WorldView::setFocus(Gtk::Widget& element){
	this->window.get_hadjustment()->set_value(element.get_allocation().get_x() - this->window.get_hadjustment()->get_page_size() / 2);
	this->window.get_vadjustment()->set_value(element.get_allocation().get_y() - this->window.get_vadjustment()->get_page_size() / 2);
}
