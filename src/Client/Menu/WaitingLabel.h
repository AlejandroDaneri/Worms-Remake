#ifndef __WAITINGLABEL_H__
#define __WAITINGLABEL_H__

#include <gtkmm/label.h>

/* Label de que indica la espera a otros jugadores */
class WaitingLabel{
	private:
		Gtk::Label label;

	public:
		/* Constructor */
		WaitingLabel();

		/* Destructor */
		~WaitingLabel();

		/* Devuelve el contenedor del mensaje */
		Gtk::Widget& getWidget();
};


#endif
