#include "ScreenView.h"

ScreenView::ScreenView(Player& player, WeaponList& weapons,TurnLabel& label, PlayersList& players) :
	weapons_view(weapons, player) {
	this->world_box.pack_start(players.getWindow(), Gtk::PACK_SHRINK);
	this->world_box.pack_start(world.getWindow());
	this->world_box.pack_end(this->weapons_view.getWindow(), Gtk::PACK_SHRINK);

	this->screen.pack_start(label.getWindow(), Gtk::PACK_SHRINK);
	this->screen.pack_end(this->world_box);
}

ScreenView::~ScreenView() {}

Gtk::Container& ScreenView::getWindow() {
	return this->screen;
}

WorldView& ScreenView::getWorld() {
    return this->world;
}

WeaponView& ScreenView::getWeaponsView() {
    return this->weapons_view;
}
