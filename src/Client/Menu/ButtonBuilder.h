#ifndef WORMS_BUTTONBUILDER_H
#define WORMS_BUTTONBUILDER_H

#include <gtkmm/button.h>

class ButtonBuilder {
public:
	/* Modifica la visualización del label del boton */
	static void buildButton(Gtk::Button* button);
};


#endif //WORMS_BUTTONBUILDER_H
