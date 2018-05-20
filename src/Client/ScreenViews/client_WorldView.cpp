#include "WorldView.h"
#include "ViewTransformer.h"
#include "client_Player.h"
#include "math_utils.h"
#include <gtkmm/adjustment.h>

const std::string NEW_TURN_MESSAGE = "Comenzó su turno";
const std::string END_TURN_MESSAGE = "Ha terminado su turno";

WorldView::WorldView(){
	this->window.add_events(Gdk::BUTTON_PRESS_MASK);
	this->window.add(this->world);
	this->window.override_background_color(Gdk::RGBA("lightgreen"));////////////// Reemplazar por fondo de pantalla
	//this->message.set_label(NEW_TURN_MESSAGE);
	//this->world.put(this->message, -100, -100);
}

WorldView::~WorldView(){}

void WorldView::moveElement(Gtk::Widget& element, const Position& position, float width, float height, bool focus){
	Position newPosition = ViewTransformer().transformToScreenAndMove(position, width, height);
	this->world.move(element, newPosition.getX(), newPosition.getY());
	if (focus){
		this->setFocus(element);
	}
}

void WorldView::moveScope(Gtk::Widget& scope, Gtk::Widget& worm, int angle) {
	float pos_x = this->world.child_property_x(worm).get_value();
	float pos_y = this->world.child_property_y(worm).get_value();
	pos_x += 50 * Math::cos_degrees(angle);
	pos_y -= 50 * Math::sin_degrees(angle);
	pos_x -= worm.get_width() / 2; // Para que quede referenciado a la mitad de la imagen
	this->world.move(scope, pos_x, pos_y);
}

void WorldView::removeElement(Gtk::Widget& element){
	this->world.remove(element);
}

void WorldView::addElement(Gtk::Widget& element, const Position& position, float width, float height, bool focus){
	Position newPosition = ViewTransformer().transformToScreenAndMove(position, width, height);
	this->world.put(element, newPosition.getX(), newPosition.getY());
	element.show_all();
	if (focus){
		this->setFocus(element);
	}
}

Gtk::ScrolledWindow& WorldView::getWindow(){
	return this->window;
}

void WorldView::setFocus(Gtk::Widget& element){
	this->window.get_hadjustment()->set_value(element.get_allocation().get_x() - this->window.get_hadjustment()->get_page_size() / 2);
	this->window.get_vadjustment()->set_value(element.get_allocation().get_y() - this->window.get_vadjustment()->get_page_size() / 2);
}

void WorldView::showNewTurn() {
	float pos_x = this->window.get_width() / 2.0;
	pos_x += this->window.get_hadjustment()->get_value();
	this->world.move(this->message, pos_x, 50);
	this->message.set_label(NEW_TURN_MESSAGE);
	this->message.show();
}

void WorldView::showEndTurn() {
	float pos_x = this->window.get_width() / 2.0;
	pos_x += this->window.get_hadjustment()->get_value();
	this->world.move(this->message, pos_x, 50);
	this->message.set_label(END_TURN_MESSAGE);
	this->message.show();
}

void WorldView::hideMessage() {
	this->message.hide();
}

