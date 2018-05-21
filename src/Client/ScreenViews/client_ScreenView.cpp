#include "client_ScreenView.h"

ScreenView::ScreenView(WorldView& world, WeaponView& weapons, TurnLabel& label) {
	this->world_label.pack_start(label.getWindow(), Gtk::PACK_SHRINK);
	this->world_label.pack_end(world.getWindow());
	this->screen.pack_start(world_label);
	this->screen.pack_end(weapons.getWindow(), Gtk::PACK_SHRINK);
}

ScreenView::~ScreenView() {}

Gtk::Container& ScreenView::getWindow() {
	return this->screen;
}

