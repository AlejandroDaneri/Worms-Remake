#include "WorldView.h"
#include "ViewTransformer.h"
#include "client_Player.h"

WorldView::WorldView(){
	this->world.add_events(Gdk::BUTTON_PRESS_MASK);
	this->window.add(this->world);
	this->window.override_background_color(Gdk::RGBA("lightgreen"));////////////// Reemplazar por fondo de pantalla
}

WorldView::~WorldView(){}

void WorldView::moveElement(Gtk::Widget& element, const Position& position){
	Position newPosition = ViewTransformer().transformToScreen(position);
	this->world.move(element, newPosition.getX(), newPosition.getY());
}

void WorldView::removeElement(Gtk::Widget& element){
	this->world.remove(element);
}

void WorldView::addElement(Gtk::Widget& element, const Position& position){
	Position newPosition = ViewTransformer().transformToScreen(position);
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

void WorldView::enable_all_handlers(Player& player) {
	this->world.signal_key_press_event().connect(sigc::mem_fun(player, &Player::complete_key_press_handler));
	this->world.signal_key_release_event().connect(sigc::mem_fun(player, &Player::complete_key_release_handler));
	this->world.signal_button_press_event().connect(sigc::mem_fun(player, &Player::on_button_press_event));
}

void WorldView::enable_movement_handlers(Player& player) {
	this->world.signal_key_press_event().connect(sigc::mem_fun(player, &Player::movement_key_press_handler));
	this->world.signal_key_release_event().connect(sigc::mem_fun(*this, &WorldView::inactive_key_handler));
	this->world.signal_button_press_event().connect(sigc::mem_fun(*this, &WorldView::inactive_button_handler));
}

void WorldView::disable_handlers() {
	this->world.signal_key_press_event().connect(sigc::mem_fun(*this, &WorldView::inactive_key_handler));
	this->world.signal_key_release_event().connect(sigc::mem_fun(*this, &WorldView::inactive_key_handler));
	this->world.signal_button_press_event().connect(sigc::mem_fun(*this, &WorldView::inactive_button_handler));
}

