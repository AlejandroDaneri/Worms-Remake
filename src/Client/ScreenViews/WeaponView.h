#ifndef __CLIENTWEAPONVIEW_H__
#define __CLIENTWEAPONVIEW_H__

#include <gtkmm/grid.h>
#include <unordered_map>
#include <memory>

class Player;
class WeaponList;
class WeaponButton;
class Weapon;

class WeaponView {
	private:
		WeaponList& weapons;
		Gtk::Grid window;
		Player& player;
		std::unordered_map<std::string, std::unique_ptr<WeaponButton>> buttons;

	public:
		WeaponView(WeaponList& weapons, Player& player);
		~WeaponView();
		
		void update();

		void updateAmmo(const Weapon& weapon);
		
		Gtk::Grid& getWindow();
};

#endif
