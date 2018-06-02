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

		bool mouseMotionEvent(GdkEventMotion* motion_event);
		bool mouseEntered(GdkEventCrossing* crossing_event);
		bool mouseLeft(GdkEventCrossing* crossing_event);

		bool scroll();

	public:
		ScrollHandler(Gtk::ScrolledWindow& window);

		~ScrollHandler();

};

#endif
