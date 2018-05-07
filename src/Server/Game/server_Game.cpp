#include "Game.h"

Game::Game(const std::string& config_file): parameters(config_file){}

Game::~Game(){}

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