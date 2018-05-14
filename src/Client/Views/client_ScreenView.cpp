#include "client_ScreenView.h"

ScreenView::ScreenView(WorldView& world, WeaponView& weapons) {
	this->screen.add(weapons.getWindow());
	this->screen.add(world.getWindow());
}

ScreenView::~ScreenView() {}

Gtk::VBox& ScreenView::getWindow() {
	return this->screen;
}

