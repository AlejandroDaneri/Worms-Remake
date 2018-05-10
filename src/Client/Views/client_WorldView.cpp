#include "WorldView.h"
#include <thread>

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
