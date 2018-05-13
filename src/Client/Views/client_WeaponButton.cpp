#include "client_WeaponButton.h"
#include "client_Player.h"

#define IMAGE_PATH "resources/images/"

WeaponButton::WeaponButton(const std::string& weapon_name, Player& player) :
	weapon_name(weapon_name), player(player) {
	std::string path = IMAGE_PATH;
	path += weapon_name + ".png";
	this->image.set(path);
	this->button.set_image(this->image);
	this->button.signal_clicked().connect(sigc::mem_fun(*this, &WeaponButton::on_clicked_button));
}

WeaponButton::~WeaponButton() {}

void WeaponButton::on_clicked_button() {
	this->button.set_active(false);	
	this->player.change_weapon(weapon_name);
}

Gtk::Widget& WeaponButton::getButton() {
	return this->button;
}

