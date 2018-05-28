#include <gtkmm/application.h>
#include <gtkmm/window.h>
#include "ServerMenu.h"

int main(int argc, char* argv[]){

	auto app = Gtk::Application::create(argc, argv);
    Gtk::Window window;
	window.maximize();

	ServerMenu server_menu(window);

	app->run(window);


	return 0;
}