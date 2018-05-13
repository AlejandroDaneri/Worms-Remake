#include "client_WeaponView.h"
#include "client_WeaponButton.h"
#include "client_Player.h"

WeaponView::WeaponView(WeaponList& weapons, Player& player) : weapons(weapons) {
	WeaponList::iterator iter;
	int row = 0, column = 0;
	for (iter = weapons.begin(); iter != weapons.end(); iter++) {
		WeaponButton button(iter->second.getName(), player);
		this->window.attach(button.getButton(), row, column, 1, 1);
		column++;
		if (column == 2) {
			column = 0;
			row++;
		}
	}
}

WeaponView::~WeaponView() {}

Gtk::Grid& WeaponView::getWindow() {
	return this->window;
}

