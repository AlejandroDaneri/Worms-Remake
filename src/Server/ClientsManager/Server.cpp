#include <string>
#include <memory>
#include <iostream>
#include "Server.h"
#include "ClientHandler.h"

#define MAX_CLIENT_WAIT 100

Server::Server(const std::string& service, std::mutex& mutex_cout): 
	socket(Socket::Server(service.c_str(), MAX_CLIENT_WAIT)),
	games_list(*this, mutex_cout), mutex_cout(mutex_cout){}

Server::~Server(){
	for (std::unique_ptr<Thread>& client: this->clients){
		client->stop();
		client->join();
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
			ServerProtocol protocol(std::move(client));
			this->addConnectedClient(std::move(protocol));

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
	this->games_list.checkGames();
	std::lock_guard<std::mutex> lock(this->mutex);
	auto it = this->clients.begin();
	while (it != this->clients.end()){
		if (!(*it)->isRunning()){
			(*it)->join();
			it = this->clients.erase(it); 
		} else {
			++it;
		}
	}
}

void Server::addConnectedClient(ServerProtocol&& protocol){
	std::lock_guard<std::mutex> lock(this->mutex);
	Thread* t = new ClientHandler(std::move(protocol), games_list, mutex_cout);
	std::unique_ptr<Thread> th(t);
	th->start();
	this->clients.push_back(std::move(th));
}
