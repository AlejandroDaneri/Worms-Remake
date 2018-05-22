#ifndef __PLAYERLIFELABEL_H__
#define __PLAYERLIFELABEL_H__

#include <gtkmm/label.h>

class PlayerLifeLabel{
	private:
		std::string player_name;
		Gtk::Label label;
		int life;

		void updateLabel();

	public:
		PlayerLifeLabel();
		~PlayerLifeLabel();

		void setPlayerName(const std::string& player_name);
		void addLife(int life);
		void reduceLife(int life);
		
		Gtk::Label& getLabel();
};


#endif
