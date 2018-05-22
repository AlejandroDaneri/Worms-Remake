#include "client_ScreenView.h"

ScreenView::ScreenView(WorldView& world, WeaponView& weapons, TurnLabel& label, PlayersList& players) {
	this->world_box.pack_start(players.getWindow(), Gtk::PACK_SHRINK);
	this->world_box.pack_start(world.getWindow());
	this->world_box.pack_end(weapons.getWindow(), Gtk::PACK_SHRINK);

	this->screen.pack_start(label.getWindow(), Gtk::PACK_SHRINK);
	this->screen.pack_end(this->world_box);
}

ScreenView::~ScreenView() {}

Gtk::Container& ScreenView::getWindow() {
	return this->screen;
}

