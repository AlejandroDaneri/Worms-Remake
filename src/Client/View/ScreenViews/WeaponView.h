#ifndef __CLIENTWEAPONVIEW_H__
#define __CLIENTWEAPONVIEW_H__

#include <gtkmm/grid.h>
#include <unordered_map>
#include <memory>
#include <string>

class Player;
class WeaponList;
class WeaponButton;
class Weapon;

/* Clase que se encarga de mostrar los datos de las armas del juego
 * y de almacenar todos los botones de las armas */
class WeaponView {
	private:
		WeaponList& weapons;
		Gtk::Grid window;
		Player& player;
		std::unordered_map<std::string, std::unique_ptr<WeaponButton>> buttons;

	public:
		/* Constructor */
		WeaponView(WeaponList& weapons, Player& player);

		/* Destructor */
		~WeaponView();


		/* Actualiza la informacion de todos los botones */
		void update();

		/* Actualiza la informacion de la municion del arma especifica */
		void updateAmmo(const Weapon& weapon);

		/* Devuelve el contenedor de la vista */
		Gtk::Grid& getWindow();
};

#endif
