#include "client_WeaponButton.h"

#define IMAGE_PATH ""

WeaponButton::WeaponButton(const std::string& weapon_name, Player& player) :
	weapon_name(weapon_name), player(player) {
	std::string path = IMAGE_PATH;
	path += weapon_name + ".png";
	this->image.set(path);
	this->button.set_image(this->image);
	this->button.signal_clicked().connect(sigc::mem_fun(*this, &WeaponButton::on_clicked_button));
}

void WeaponButton::on_clicked_button() {
	this->player.change_weapon(weapon_name);
}

Gtk::Widget& WeaponButton::getButton() {
	return this->button;
}

WeaponButton::~WeaponButton() {}

