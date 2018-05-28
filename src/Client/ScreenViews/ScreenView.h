#ifndef __CLIENTSCREENVIEW_H__
#define __CLIENTSCREENVIEW_H__

#include <gtkmm/hvbox.h>
#include <gtkmm/label.h>
#include "WorldView.h"
#include "WeaponView.h"
#include "TurnLabel.h"
#include "PlayersList.h"

/* Clase que se encarga de almacenar los contenedores principales
 * de la vista y mostrar su contenido */
class ScreenView {
	private:
		Gtk::VBox screen;
		Gtk::HBox world_box;

        WorldView world;
        WeaponView weapons_view;

	public:
        /* Constructor */
		ScreenView(Player& player, WeaponList& weapons,TurnLabel& label, PlayersList& players);

        /* Destructor */
        ~ScreenView();


        /* Devuelve el contenedor de la vista */
		Gtk::Container& getWindow();

        /* Devuelve el WorldView */
        WorldView& getWorld();

        /* Devuelve el WeaponView */
        WeaponView& getWeaponsView();
};

#endif
