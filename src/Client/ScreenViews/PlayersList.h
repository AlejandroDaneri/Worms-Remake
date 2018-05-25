#ifndef __PLAYERSLIST_H__
#define __PLAYERSLIST_H__

#include <map>
#include <string>
#include "PlayerLifeLabel.h"
#include <gtkmm/hvbox.h>

class PlayersList{
	private:
		std::map<int, std::string> players;
		std::map<int, PlayerLifeLabel> labels;
		Gtk::VBox container;

	public:
		/* Constructor */
		PlayersList();

		/* Destructor */
		~PlayersList();

		/* Agrega al jugador a la lista de jugadores y agrega su
		 * informacion a la vista */
		void addPlayer(int id, const std::string& name);

		/* Devuelve el nombre del jugador */
		const std::string& getPlayer(int id) const;

		/* Devuelve el contenedor de los jugadores */
		Gtk::Container& getWindow();

		/* Agrega la informacion de la vida del jugador a la vista */
		void addPlayerLife(int player_id, int life);

		/* Reduce la vida del jugador y actualiza la vista */
		void reducePlayerLife(int player_id, int life);
};

#endif
