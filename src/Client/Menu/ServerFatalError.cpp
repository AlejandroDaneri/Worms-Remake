#include "ServerFatalError.h"
#include <gtkmm/messagedialog.h>

ServerFatalError::ServerFatalError(Gtk::Window& window){
	Gtk::MessageDialog dialog(window, "Ocurrio un error con la conexion del servidor", false, Gtk::MESSAGE_ERROR, Gtk::BUTTONS_CLOSE, true);
	dialog.run();
	window.close();
}

ServerFatalError::~ServerFatalError(){}