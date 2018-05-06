#include <gtkmm/application.h>
#include <gtkmm/window.h>
#include "WorldView.h"
#include "WormView.h"
#include "WeaponView.h"
#include "ViewsList.h"

#include "World.h"
#include "Worm.h"
#include "DataSender.h"

int main(int argc, char* argv[]){
	auto app = Gtk::Application::create(argc, argv);
    Gtk::Window window;
    window.resize(1000, 1000);

    WorldView world;

    WormView worm(world, 100, Position(50, 50));
    WormView worm2(world, 100, Position(500, 500));
    worm2.updateData(100, DIR_LEFT, Position(500, 500));

    WeaponView weapon(world, "missile", Position(700,150));

    ViewsList list;
    list.addWorm(std::move(worm), 1);
    list.addWorm(std::move(worm2), 2);
    list.addWeapon(std::move(weapon), 1);

    window.add(world.getWindow());
    window.show_all();

    ///Cosas del server para probar

    World world_server(b2Vec2(0.0f, 10.0));

    physical_object_ptr worm_server(new Worm(world_server, 1));
    world_server.addObject(worm_server, b2Vec2(500, 500));

    physical_object_ptr worm2_server(new Worm(world_server, 2));
    world_server.addObject(worm2_server, b2Vec2(600, 500));

    DataSender sender(world_server, list);

    world_server.start();
    sender.start();
    
    ///////////
    app->run(window);

    world_server.stop();
    world_server.join();
    sender.stop();
    sender.join();

	return 0;
}
