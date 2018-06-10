#include "ServerFatalError.h"
#include <gtkmm/messagedialog.h>
#include <string>

const std::string ERROR_MSG("Ocurrio un error con la conexion del servidor");

ServerFatalError::ServerFatalError(Gtk::Window& window) {
	Gtk::MessageDialog dialog(window, ERROR_MSG, false, Gtk::MESSAGE_ERROR,
							  Gtk::BUTTONS_CLOSE, true);
	dialog.run();
	window.close();
}

ServerFatalError::~ServerFatalError() {}
