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
		server.start();
		while (std::cin.get() != EXIT_CHAR){}
		server.stop();
		server.join();
	} catch(const std::exception& e){
		std::cerr << e.what() << std::endl;
	}
	return 0;
}
