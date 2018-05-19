#include "WorldView.h"
#include "ViewTransformer.h"
#include "client_Player.h"
#include "math_utils.h"

WorldView::WorldView(Player& player): player(player) {
	this->window.add_events(Gdk::BUTTON_PRESS_MASK);
	this->window.add(this->world);
	this->window.override_background_color(Gdk::RGBA("lightgreen"));////////////// Reemplazar por fondo de pantalla
}

WorldView::~WorldView(){}

void WorldView::moveElement(Gtk::Widget& element, const Position& position, float width, float height){
	Position newPosition = ViewTransformer().transformToScreenAndMove(position, width, height);
	this->world.move(element, newPosition.getX(), newPosition.getY());
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

void WorldView::addElement(Gtk::Widget& element, const Position& position, float width, float height){
	Position newPosition = ViewTransformer().transformToScreenAndMove(position, width, height);
	this->world.put(element, newPosition.getX(), newPosition.getY());
	element.show();
}

Gtk::ScrolledWindow& WorldView::getWindow(){
	return this->window;
}

bool WorldView::inactive_key_handler(GdkEventKey* key_event) {
	return true;
}

bool WorldView::inactive_button_handler(GdkEventButton *event) {
	return true;
}

void WorldView::enable_all_handlers() {
	this->window.get_parent()->signal_key_press_event().connect(sigc::mem_fun(player, &Player::complete_key_press_handler));
	this->window.get_parent()->signal_key_release_event().connect(sigc::mem_fun(player, &Player::complete_key_release_handler));
	this->window.signal_button_press_event().connect(sigc::mem_fun(player, &Player::on_button_press_event));
}

void WorldView::enable_movement_handlers() {
	this->window.get_parent()->signal_key_press_event().connect(sigc::mem_fun(player, &Player::movement_key_press_handler));
	this->window.get_parent()->signal_key_release_event().connect(sigc::mem_fun(*this, &WorldView::inactive_key_handler));
	this->window.signal_button_press_event().connect(sigc::mem_fun(*this, &WorldView::inactive_button_handler));
}

void WorldView::disable_handlers() {
	this->window.get_parent()->signal_key_press_event().connect(sigc::mem_fun(*this, &WorldView::inactive_key_handler));
	this->window.get_parent()->signal_key_release_event().connect(sigc::mem_fun(*this, &WorldView::inactive_key_handler));
	this->window.signal_button_press_event().connect(sigc::mem_fun(*this, &WorldView::inactive_button_handler));
}

