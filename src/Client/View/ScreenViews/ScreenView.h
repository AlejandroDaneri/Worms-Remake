#ifndef __CLIENTSCREENVIEW_H__
#define __CLIENTSCREENVIEW_H__

#include <gtkmm/hvbox.h>
#include <gtkmm/label.h>
#include <gtkmm/window.h>
#include <string>
#include "MenuView.h"
#include "WorldView.h"
#include "WeaponView.h"
#include "TurnLabel.h"
#include "PlayersList.h"
#include "WindView.h"
#include "VictoryWindow.h"

/* Clase que se encarga de almacenar los contenedores principales
 * de la vista y mostrar su contenido */
class ScreenView {
private:
	Gtk::VBox screen;
	Gtk::HBox world_box;
	Gtk::VBox left_view;
	Gtk::Window& window;

	WorldView world;
	WeaponView weapons_view;
	TurnLabel turn_label;
	PlayersList players;
	WindView wind_view;

	VictoryWindow victory_view;

	/* CallBacks */
	bool showCallBack();

	bool closeCallBack();

public:
	/* Constructor */
	ScreenView(Gtk::Window& window, MenuView& main_menu, Player& player,
			   WeaponList& weapons);

	/* Destructor */
	~ScreenView();

	/* Muestra la pantalla en la ventana */
	void show();

	/* Cierra la ventana completamente */
	void close();

	/* Devuelve el WorldView */
	WorldView& getWorld();

	/* Devuelve el WeaponView */
	WeaponView& getWeaponsView();

	/* Devuelve el TurnLabel */
	TurnLabel& getTurnLabel();

	/* Devuelve el Players view */
	PlayersList& getPlayersView();

	/* Devuelve el wind view */
	WindView& getWindView();

	/* Muestra una ventana con el ganador */
	void setWinner(const std::string& winner, bool i_win);
};

#endif
