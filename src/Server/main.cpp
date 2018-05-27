#include "Server.h"
#include <iostream>
#include <memory>
#include "Thread.h"

#define EXIT_CHAR 'q'

/*
int main(int argc, const char* argv[]){
	std::unique_ptr<Thread> thread;
	try{
		thread = std::unique_ptr<Thread>(new Server("7777"));
		thread->start();
		while (std::cin.get() != EXIT_CHAR){}
	} catch(const std::exception& e){
		std::cerr << e.what() << std::endl;
	}

	if (thread){
		thread->stop();
		thread->join();
	}
	return 0;
}

////*/
