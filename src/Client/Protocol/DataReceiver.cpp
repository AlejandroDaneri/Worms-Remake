#include "DataReceiver.h"
#include "Player.h"
#include <iostream>

DataReceiver::DataReceiver(Player& player): 
	player(player), protocol(player.getProtocol()){}

DataReceiver::~DataReceiver(){}

void DataReceiver::run(){
	try{
		this->initialConfig();
		while(this->running){
			this->protocol.receive(this->player);
		}

	} catch (const std::exception& e){
		if (this->running){
			std::cerr << "Ocurrio un error: " << e.what() << std::endl;
			this->player.getScreen().close();
		}
	}
	
}

void DataReceiver::stop(){
	Thread::stop();
	this->protocol.stop();
}

void DataReceiver::initialConfig(){
	this->protocol.receiveChar();
	this->protocol.receivePlayers(this->player.getScreen().getPlayersView());
	this->protocol.receiveGirders(this->player.getViewsList());
	this->protocol.receiveWeaponsAmmo(this->player.getWeapons());
	this->player.getScreen().show();
}
