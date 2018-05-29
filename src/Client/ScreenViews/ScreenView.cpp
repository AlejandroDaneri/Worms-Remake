#include "ScreenView.h"
#include <glibmm/main.h>

ScreenView::ScreenView(Gtk::Window& window, Player& player, WeaponList& weapons) :
	window(window), weapons_view(weapons, player) {
	this->world_box.pack_start(this->players.getWindow(), Gtk::PACK_SHRINK);
	this->world_box.pack_start(this->world.getWindow());
	this->world_box.pack_end(this->weapons_view.getWindow(), Gtk::PACK_SHRINK);

	this->screen.pack_start(this->turn_label.getWindow(), Gtk::PACK_SHRINK);
	this->screen.pack_end(this->world_box);
}

ScreenView::~ScreenView() {}

void ScreenView::show(){
	sigc::slot<bool> my_slot = sigc::mem_fun(*this, &ScreenView::showCallBack);
    Glib::signal_idle().connect(my_slot);
}

bool ScreenView::showCallBack(){
	this->weapons_view.update();
	this->window.remove();
	this->window.add(this->screen);
	this->window.show_all();
	return false;
}

WorldView& ScreenView::getWorld() {
    return this->world;
}

WeaponView& ScreenView::getWeaponsView() {
    return this->weapons_view;
}

TurnLabel& ScreenView::getTurnLabel(){
	return this->turn_label;
}

PlayersList& ScreenView::getPlayersView(){
	return this->players;
}
