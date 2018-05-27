#include "CreateGameMenu.h"

CreateGameMenu::CreateGameMenu(Gtk::Window& window, ClientProtocol&& protocol, std::string&& name):
	window(window), protocol(std::move(protocol)), player_name(std::move(player_name)){}

CreateGameMenu::~CreateGameMenu(){}
