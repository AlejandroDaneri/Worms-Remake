#ifndef __HANDLERS__H__
#define __HANDLERS__H__

#include <gdk/gdk.h>
#include "WeaponPowerAccum.h"
#include "ScrollHandler.h"

class Player;

class ViewsList;

class WeaponList;

class WorldView;

/* Clase que se encarga de definir los handlers del teclado y 
   del mouse. */
class Handlers {
private:
	Player& player;
	ViewsList& view_list;
	WeaponList& weapons;
	WorldView& world;
	ScrollHandler scroll_handler;

	bool has_shoot;
	int current_angle;
	int weapons_time;
	bool enabled;

	WeaponPowerAccum power_accumulator;


public:
	/* Constructor */
	Handlers(Player& player, ViewsList& view_list, WeaponList& weapons,
			 WorldView& world);

	/* Destructor */
	~Handlers();

	/* Handler completo para el presionado de teclas. Indica
	   los pasos que se deben realizar al presionar una tecla
	   especifica */
	bool keyPressHandler(GdkEventKey* key_event);

	/* Handler completo para la liberación de teclas. Indica
	   los pasos que se deben realizar al liberar una tecla
	   especifica */
	bool keyReleaseHandler(GdkEventKey* key_event);

	/* Handler del mouse. Indica los pasos que se deben realizar
	   al utilizar el mouse */
	bool onButtonPressEvent(GdkEventButton* event);

	/* Habilita todos los handlers */
	void enableAll();

	/* Deshabilita todos los handlers */
	void disableAll();

	/* Devuelve true si los handlers estan habilitados */
	bool isEnabled() const;

	/* Realiza el shoot del player */
	void powerAccumStopped(int power);

	/* Devuelve el angulo actual del scope */
	int getCurrentAngle() const;

	/* Detiene los handlers */
	void stop();
};

#endif
