#include <string>
#include <memory>
#include <iostream>
#include "Server.h"
#include "ClientHandler.h"

#define MAX_CLIENT_WAIT 100

Server::Server(const std::string& service, std::mutex& mutex_cout): 
	socket(Socket::Server(service.c_str(), MAX_CLIENT_WAIT)), games_list(mutex_cout), mutex_cout(mutex_cout){}

Server::~Server(){
	for (auto it = this->clients.begin(); it != this->clients.end(); ++it){
		(*it)->stop();
		(*it)->join();
	}
}

void Server::run(){
	while (this->running){
		try{
			Socket client = this->socket.acceptClient();
			{
				std::lock_guard<std::mutex> lock(this->mutex_cout);
				std::cout << "[INFO] Nuevo cliente conectado." << std::endl;
			}
			std::unique_ptr<Thread> t(new ClientHandler(std::move(client), this->games_list, this->mutex_cout));
			t->start();
			this->clients.push_back(std::move(t));

			this->check();
		} catch(const std::exception& e){
			if (this->running){
				std::lock_guard<std::mutex> lock(this->mutex_cout);
				std::cout << "[ERROR] " << e.what() << std::endl;
			}
		}
	}
}

void Server::stop(){
	this->running = false;
	this->socket.stop();
}

void Server::check(){
	//Elimino threads que ya terminaron
	auto it = this->clients.begin();
	while (it != this->clients.end()){
		if (!(*it)->isRunning()){
			(*it)->join();
			it = this->clients.erase(it); 
		} else {
			++it;
		}
	}

	this->games_list.checkGames();
}
