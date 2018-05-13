#include "client_WeaponButton.h"

#define IMAGE_PATH ""

WeaponButton::WeaponButton(std::string& weapon_name) {
	std::string path = IMAGE_PATH;
	path += weapon_name + ".png";
	this->image.set(path);
	this->button.set_image(this->image);
}

Gtk::Widget& WeaponButton::getButton() {
	return this->button;
}

WeaponButton::~WeaponButton() {}
