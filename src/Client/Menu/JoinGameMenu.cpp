#include "JoinGameMenu.h"

JoinGameMenu::JoinGameMenu(Gtk::Window& window, ClientProtocol&& protocol, std::string&& name, int quantity):
	window(window), protocol(std::move(protocol)), player_name(std::move(player_name)){}

JoinGameMenu::~JoinGameMenu(){}