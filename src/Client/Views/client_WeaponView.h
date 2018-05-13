#ifndef __CLIENTWEAPONVIEW_H__
#define __CLIENTWEAPONVIEW_H__

#include <gtkmm/grid.h>
#include <unordered_map>


class Player;
class WeaponList;
class WeaponButton;

class WeaponView {
	private:
		WeaponList& weapons;
		Gtk::Grid window;
		Player& player;
		std::unordered_map<std::string, WeaponButton*> buttons;

	public:
		WeaponView(WeaponList& weapons, Player& player);
		~WeaponView();
		
		void update();
		
		Gtk::Grid& getWindow();
};

#endif
