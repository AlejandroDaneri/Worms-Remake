#include "Server.h"
#include "yaml.h"
#include "ConfigFields.h"
#include "Path.h"
#include <iostream>
#include <string>
#include <mutex>

#define EXIT_CHAR 'q'

int main(int argc, const char* argv[]){
	std::mutex mutex_cout;
	try{
		YAML::Node config(YAML::LoadFile(SERVER_CONFIG_FILE));
		Server server(config[SERVER_PORT].as<std::string>(), mutex_cout);
		std::cout << "[LOG] Server iniciado." << std::endl;
		server.start();
		while (std::cin.get() != EXIT_CHAR){}
		{
			std::lock_guard<std::mutex> lock(mutex_cout);
			std::cout << "[LOG] Comenzando el cierre del servidor." << std::endl;
		}
		server.stop();
		server.join();
	} catch(const std::exception& e){
		std::lock_guard<std::mutex> lock(mutex_cout);
		std::cout << "[ERROR] " << e.what() << std::endl;
	}
	return 0;
}
