#include "Game.h"
#include "DataSender.h"
#include "Girder.h"
#include "server_WeaponFactory.h"


Game::Game(const std::string& config_file): parameters(config_file){}

Game::~Game(){
	this->world.stop();
	this->world.join();
	this->data_sender->stop();
	this->data_sender->join();
	
}

bool Game::addPlayer(Player&& player){
	std::lock_guard<std::mutex> lock(this->mutex);

	if (this->isFull()){
		return false;
	}

	this->turn.addPlayer(std::move(player));
	return true;
}

bool Game::isFull(){
	return this->parameters.get_max_players() == this->turn.get_players_size();
}

void Game::run(){
	this->configure();
	this->world.start();
	this->data_sender->start();

	worm_ptr worm(new Worm(this->world, 38, this->parameters));
	this->world.addObject(worm, b2Vec2(10, 25));
	physical_object_ptr girder(new Girder(this->world, 6));
	this->world.addObject(girder, b2Vec2(7, 20));

	sleep(5);
	//worm->changeWeapon("Banana");
	//worm->shoot(60, -1, 15);
	worm->changeWeapon("AirAttack");
	worm->shoot(b2Vec2(20, 50));
}

void Game::configure(){
	this->data_sender.reset(new DataSender(this->world, this->turn.getPlayers()));

	for (int i = 1; i < 5; i++){
		physical_object_ptr worm(new Worm(this->world, i, this->parameters));
		this->world.addObject(worm, b2Vec2(10 * (i+1), 75));
		physical_object_ptr girder(new Girder(this->world, 6));
		this->world.addObject(girder, b2Vec2(10 * (i+1) - 3, 20));
		//agegar worm al jugador etc
		//recibir los worms del gameparameters
		//antes enviar a todos los jugadores vigas, municiones, etc
	}

}

worm_ptr Game::getCurrentWorm(){
	return this->turn.getCurrentPlayer().getCurrentWorm();
}

void Game::endTurn(){
	///////////////////////////////
}
