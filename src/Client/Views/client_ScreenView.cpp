#include "client_ScreenView.h"

ScreenView::ScreenView(WorldView& world, WeaponView& weapons) {
	//this->screen.add(weapons.getWindow());
	//this->screen.add(world.getWindow());
	this->screen.pack_start(world.getWindow());
	this->screen.pack_end(weapons.getWindow(), Gtk::PACK_SHRINK);
}

ScreenView::~ScreenView() {}

Gtk::HBox& ScreenView::getWindow() {
	return this->screen;
}

