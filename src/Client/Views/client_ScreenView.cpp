#include "client_ScreenView.h"

ScreenView::ScreenView(WorldView& world, WeaponView& weapons) {
	this->screen.add(world.getWindow());
	this->screen.add(weapons.getWindow());
}

ScreenView::~ScreenView() {}

Gtk::HBox& ScreenView::getWindow() {
	return this->screen;
}

