#include <string>
#include <memory>
#include "Server.h"
#include "ClientHandler.h"

#define MAX_CLIENT_WAIT 100

Server::Server(const std::string& service): 
	socket(Socket::Server(service.c_str(), MAX_CLIENT_WAIT)){}

Server::~Server(){
	for (auto it = this->clients.begin(); it != this->clients.end(); ++it){
		(*it) -> stop();
		(*it) -> join();
	}
}

void Server::run(){
	while (this->running){
		try{
			Socket client = this->socket.accept_client();
			std::unique_ptr<Thread> t(new ClientHandler(std::move(client), this->games_list));
			t->start();
			this->clients.push_back(std::move(t));

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
		} catch(const std::exception& e){
			if (this->running){
				throw e;
			}
		}
	}
}

void Server::stop(){
	this->running = false;
	this->socket.stop();
}
