#include "Game.h"
#include "DataSender.h"

Game::Game(const std::string& config_file): parameters(config_file), world(b2Vec2(0.0f, 10.0)){}

Game::~Game(){}

bool Game::addPlayer(Player&& player){
	std::lock_guard<std::mutex> lock(this->mutex);

	if (this->isFull()){
		return false;
	}

	std::unique_ptr<Thread> sender(new DataSender(this->world, player.getProtocol()));
	this->threads.push_back(std::move(sender));

	this->turn.addPlayer(std::move(player));
	return true;
}

bool Game::isFull(){
	return this->parameters.get_max_players() == this->turn.get_players_size();
}

void Game::run(){
	this->configure();
	////////////////////////////////////////////
}

void Game::configure(){
	////////////////////////////////////////////
}

worm_ptr Game::getCurrentWorm(){
	return this->turn.getCurrentPlayer().getCurrentWorm();
}

void Game::endTurn(){
	///////////////////////////////
}