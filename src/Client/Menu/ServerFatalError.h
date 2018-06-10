#ifndef __SERVERFATALERROR_H__
#define __SERVERFATALERROR_H__

#include <gtkmm/window.h>

/* Clase que se encarga de mostrar un error fatal
 * con la conexión entre el servidor y el cliente */
class ServerFatalError{
	public:
		/* Constructor */
		ServerFatalError(Gtk::Window& window);

		/* Destructor */
		~ServerFatalError();
};

#endif