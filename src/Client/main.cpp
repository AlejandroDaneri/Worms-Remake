#include <gtkmm/application.h>
#include <gtkmm/window.h>
#include "ServerMenu.h"
#include "Path.h"

int main(int argc, char* argv[]) {
	auto app = Gtk::Application::create(argc, argv);
	Gtk::Window window;
	window.maximize();

	window.set_title(CLIENT_WINDOW_NAME);

	window.set_icon_from_file(ICON_PATH);

	ServerMenu server_menu(window);

	app->run(window);

	return 0;
}
