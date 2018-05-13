#include "client_WeaponView.h"
#include "client_Player.h"
#include "client_WeaponList.h"
#include "client_WeaponButton.h"

WeaponView::WeaponView(WeaponList& weapons, Player& player) : 
					weapons(weapons), player(player) {
}

WeaponView::~WeaponView() {
	//printf("Destruyo");
	std::unordered_map<std::string, WeaponButton*>::iterator iter;
	for (iter = this->buttons.begin(); iter != this->buttons.end(); iter++) {
		delete iter->second;
	}
}

void WeaponView::update() {
	//printf("Hizo el update\n");
	WeaponList::iterator iter;
	int row = 1, column = 1;
	for (iter = this->weapons.begin(); iter != this->weapons.end(); iter++) {
		this->buttons.insert(std::pair<std::string, WeaponButton*>(iter->second.getName(), new WeaponButton(iter->second.getName(), this->player)));
		this->window.attach(this->buttons.at(iter->second.getName())->getButton(), row, column, 10, 10);
		column++;
		if (column == 3) {
			column = 1;
			row++;
		}
	}
}

Gtk::Grid& WeaponView::getWindow() {
	return this->window;
}

