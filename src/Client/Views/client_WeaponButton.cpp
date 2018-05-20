#include "client_WeaponButton.h"
#include "client_Player.h"

#define IMAGE_PATH "resources/images/Weapons_icons/"

WeaponButton::WeaponButton(const std::string& weapon_name, unsigned int ammo, Player& player) :
	weapon_name(weapon_name), player(player) {
	this->setLabel(ammo);
	std::string path = IMAGE_PATH;
	path += weapon_name + ".png";
	this->image.set(path);
	this->button.set_image(this->image);
	this->button.set_always_show_image(true);
	this->button.signal_clicked().connect(sigc::mem_fun(*this, &WeaponButton::on_clicked_button));
}

WeaponButton::~WeaponButton() {}

void WeaponButton::on_clicked_button() {
	this->player.change_weapon(weapon_name);
}

Gtk::Widget& WeaponButton::getButton() {
	return this->button;
}

void WeaponButton::setLabel(unsigned int ammo){
	std::string label = "Ammo:\n    ";
	if (ammo > 100){
		label += "inf";
	} else {
		label += std::to_string(ammo);
	}
	this->button.set_label(label);
}

