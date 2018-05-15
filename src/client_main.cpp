#include <gtkmm/application.h>
#include <gtkmm/window.h>
#include "WorldView.h"
#include "WormView.h"
#include "client_BulletView.h"
#include "ViewsList.h"
#include "Socket.h"
#include "client_Protocol.h"
#include "client_Player.h"
#include "DataReceiver.h"

#include <iostream>

int main(int argc, char* argv[]){

	auto app = Gtk::Application::create(argc, argv);
    Gtk::Window window;
    window.resize(1280, 720);
	try {
    	Socket socket(Socket::Client("127.0.0.1", "7777"));
    
		ClientProtocol protocol(std::move(socket));

		Player player(protocol);

		window.add(player.getWindow());
		window.show_all();

		app->run(window);
    } catch (const std::exception& e){
    	std::cout << e.what() << std::endl;
    	return 1;
    }

	return 0;
}
