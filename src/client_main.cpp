#include <gtkmm/application.h>
#include <gtkmm/window.h>
#include "WorldView.h"
#include "WormView.h"

int main(int argc, char* argv[]){
	auto app = Gtk::Application::create(argc, argv);
    Gtk::Window window;
    window.resize(1000, 1000);

    WorldView world;

    WormView worm(world, 100, Position(50, 50));
    WormView worm2(world, 100, Position(500, 500));
    worm2.updateData(100, DIR_LEFT, Position(500, 500));

    window.add(world.getWindow());
    window.show_all();

    app->run(window);

	return 0;
}