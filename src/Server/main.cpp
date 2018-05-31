#include "Server.h"
#include "yaml.h"
#include "ConfigFields.h"
#include "Path.h"
#include <iostream>

#define EXIT_CHAR 'q'

int main(int argc, const char* argv[]){
	try{
		YAML::Node config(YAML::LoadFile(SERVER_CONFIG_FILE));
		Server server(config[SERVER_PORT].as<std::string>());
		std::cout << "[LOG] Server iniciado." << std::endl;
		server.start();
		while (std::cin.get() != EXIT_CHAR){}
		std::cout << "[LOG] Comenzando el cierre del servidor." << std::endl;
		server.stop();
		server.join();
		std::cout << "[LOG] Servidor cerrado." << std::endl;
	} catch(const std::exception& e){
		std::cout << "[ERROR] " << e.what() << std::endl;
	}
	return 0;
}
