#include "WeaponButton.h"
#include <string>
#include "Player.h"
#include "Path.h"

WeaponButton::WeaponButton(const std::string& weapon_name, unsigned int ammo,
						   Player& player) :
		weapon_name(weapon_name), player(player) {
	this->setLabel(ammo);
	std::string path = WEAPONS_PATH;
	path += weapon_name + ".png";
	this->image.set(path);
	this->button.set_image(this->image);
	this->button.set_always_show_image(true);
	this->button.signal_clicked().connect(
			sigc::mem_fun(*this, &WeaponButton::onClickedButton));
}

WeaponButton::~WeaponButton() {}

void WeaponButton::onClickedButton() {
	this->player.changeWeapon(weapon_name);
}

Gtk::Widget& WeaponButton::getButton() {
	return this->button;
}

void WeaponButton::setLabel(unsigned int ammo) {
	std::string label = "Ammo:\n    ";
	if (!ammo) {
		label += "0";
		button.set_sensitive(false);
	} else if (ammo > 100) {
		label += "∞";
	} else {
		label += std::to_string(ammo);
	}
	this->button.set_label(label);
}

