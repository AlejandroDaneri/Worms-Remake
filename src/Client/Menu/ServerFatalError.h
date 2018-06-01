#ifndef __SERVERFATALERROR_H__
#define __SERVERFATALERROR_H__

#include <gtkmm/window.h>

class ServerFatalError{
	public:
		ServerFatalError(Gtk::Window& window);

		~ServerFatalError();
};

#endif