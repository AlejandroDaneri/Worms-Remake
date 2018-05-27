#include <gtkmm/application.h>
#include <gtkmm/window.h>
#include "Socket.h"
#include "ClientProtocol.h"
#include "Player.h"
#include "MusicPlayer.h"

#include <iostream>


/*
int main(int argc, char* argv[]){

	auto app = Gtk::Application::create(argc, argv);
    Gtk::Window window;
    window.resize(1280, 720);
	try {

    	Socket socket(Socket::Client("127.0.0.1", "7777"));
    
		ClientProtocol protocol(std::move(socket));

		Player player(std::move(protocol), "Pepe");////////por ahora agrego el nombre asi

		window.add(player.getWindow());
		window.show_all();
		window.maximize();
		musicPlayer.playMusic();
		app->run(window);
    } catch (const std::exception& e){
    	std::cout << e.what() << std::endl;
    	return 1;
    }

	return 0;
}
///*/
