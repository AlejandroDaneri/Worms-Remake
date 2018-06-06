#include "ScreenView.h"
#include "ServerFatalError.h"
#include <glibmm/main.h>

#define PADDING 10
#define SPACING 30

ScreenView::ScreenView(Gtk::Window& window, Player& player, WeaponList& weapons) :
	left_view(false, SPACING), window(window), weapons_view(weapons, player) {
	this->left_view.pack_start(this->wind_view.getWindow(), Gtk::PACK_SHRINK);
	this->left_view.pack_start(this->players.getWindow(), Gtk::PACK_SHRINK);
	this->world_box.pack_start(this->left_view, Gtk::PACK_SHRINK, PADDING);
	this->world_box.pack_start(this->world.getContainer());
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

void ScreenView::close(){
	sigc::slot<bool> my_slot = sigc::mem_fun(*this, &ScreenView::closeCallBack);
	Glib::signal_idle().connect(my_slot);
}

bool ScreenView::closeCallBack(){
	ServerFatalError error(this->window);
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

WindView& ScreenView::getWindView(){
	return this->wind_view;
}
