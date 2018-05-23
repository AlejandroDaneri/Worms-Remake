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
		PlayersList();

		~PlayersList();

		void addPlayer(int id, const std::string& name);

		const std::string& getPlayer(int id) const;

		Gtk::Container& getWindow();

		void addPlayerLife(int player_id, int life);
		void reducePlayerLife(int player_id, int life);
};

#endif
