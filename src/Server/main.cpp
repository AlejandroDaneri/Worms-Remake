#include "Server.h"
#include <iostream>
#include <memory>

#define EXIT_CHAR 'q'

int main(int argc, const char* argv[]){
	try{
		Server server("7777");
		server.start();
		while (std::cin.get() != EXIT_CHAR){}
		server.stop();
		server.join();
	} catch(const std::exception& e){
		std::cerr << e.what() << std::endl;
	}
	return 0;
}
