#include "Game.h"
#include "DataSender.h"

Game::Game(const std::string& config_file): parameters(config_file), world(b2Vec2(0.0f, 10.0)){}

Game::~Game(){
	this->world.stop();
	this->world.join();
	for (size_t i = 0; i < this->threads.size(); i++){
		this->threads[i]->stop();
		this->threads[i]->join();
	}
}

bool Game::addPlayer(Player&& player){
	std::lock_guard<std::mutex> lock(this->mutex);

	if (this->isFull()){
		return false;
	}

	this->turn.addPlayer(std::move(player));
	std::unique_ptr<Thread> sender(new DataSender(this->world, this->turn.getCurrentPlayer().getProtocol()));
	this->threads.push_back(std::move(sender));
	return true;
}

bool Game::isFull(){
	return this->parameters.get_max_players() == this->turn.get_players_size();
}

void Game::run(){
	this->configure();
	this->world.start();
	for (size_t i = 0; i < this->threads.size(); i++){
		this->threads[i]->start();
	}
}

void Game::configure(){
	for (int i = 0; i < 5; i++){
		physical_object_ptr worm(new Worm(this->world, i));
		this->world.addObject(worm, b2Vec2(100 * (i+1), 50));
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