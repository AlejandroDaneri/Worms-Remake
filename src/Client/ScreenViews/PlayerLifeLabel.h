#ifndef __PLAYERLIFELABEL_H__
#define __PLAYERLIFELABEL_H__

#include <gtkmm/label.h>

class PlayerLifeLabel{
	private:
		std::string player_name;
		Gtk::Label label;
		int life;

		/* Actualiza la informacion del label */
		void updateLabel();

	public:
	    /* Constructor */
		PlayerLifeLabel();

		/* Destructor */
		~PlayerLifeLabel();


		/* Establece el nombre del jugador */
		void setPlayerName(const std::string& player_name);

		/* Agrega la vida al label */
		void addLife(int life);

		/* Disminuye la vida y actualiza la vista del label */
		void reduceLife(int life);

		/* Devuelve el label del jugador */
		Gtk::Label& getLabel();
};


#endif
