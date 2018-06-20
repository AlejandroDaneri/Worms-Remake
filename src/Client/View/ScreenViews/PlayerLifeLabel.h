#ifndef __PLAYERLIFELABEL_H__
#define __PLAYERLIFELABEL_H__

#include <gtkmm/label.h>
#include <gtkmm/hvbox.h>
#include <string>

/* Clase que se encarga de controlar el indicador de vida del jugador */
class PlayerLifeLabel {
private:
	int id;
	std::string player_name;
	int life;
	Gtk::HBox container;
	Gtk::Label info_label;
	Gtk::Label id_label;

	/* Actualiza la informacion del label */
	void updateLabel();

public:
	/* Constructor */
	PlayerLifeLabel();

	/* Destructor */
	~PlayerLifeLabel();


	/* Establece el nombre del jugador */
	void setPlayerName(int id, const std::string& player_name);

	/* Agrega la vida al label */
	void addLife(int life);

	/* Disminuye la vida y actualiza la vista del label */
	void reduceLife(int life);

	/* Devuelve el contenedor con la informacion del jugador */
	Gtk::HBox& getContainer();
};


#endif
