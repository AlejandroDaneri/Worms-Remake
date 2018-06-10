#ifndef __SCROLLHADNLER_H__
#define __SCROLLHADNLER_H__

#include <gtkmm/scrolledwindow.h>
#include <gdk/gdk.h>
#include "Position.h"

class ScrollHandler{
	private:
		Gtk::ScrolledWindow& window;
		Position last_mouse_position;
		bool mouse_in_window;
		sigc::connection my_connection;

		/* Handler del movimiento del mouse */
		bool mouseMotionEvent(GdkEventMotion* motion_event);

		/* Handler de entrada en el area de desplazamiento */
		bool mouseEntered(GdkEventCrossing* crossing_event);

		/* Handler de salida del area de desplazamiento */
		bool mouseLeft(GdkEventCrossing* crossing_event);

		/* Realiza el desplazamiento de la pantalla */
		bool scroll();

	public:
		/* Constructor */
		explicit ScrollHandler(Gtk::ScrolledWindow& window);

		/* Destructor */
		~ScrollHandler();

		/* Detiene el desplazamiento */
		void stop();
};

#endif
