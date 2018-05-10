#include "WorldView.h"
#include "ViewTransformer.h"
#include "client_Player.h"

WorldView::WorldView(){
	this->window.add(this->world);
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

bool WorldView::inactive_handler(GdkEventKey* key_event) {
	return true;
}

void WorldView::enable_handlers(Player& player) {
	this->world.signal_key_press_event().connect(sigc::mem_fun(player, &Player::complete_handler));
}

void WorldView::disable_handlers() {
	this->world.signal_key_press_event().connect(sigc::mem_fun(*this, &WorldView::inactive_handler));
}

