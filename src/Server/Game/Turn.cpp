#include "Turn.h"

Turn::Turn(): current(0){}

Turn::~Turn(){}

bool Turn::addPlayer(Player& player){
	if (!this->playerCanJoin(player.getName())){
		return false;
	}
	player.setId(this->players.size());
    player.getProtocol().sendChar(true);
	this->players.push_back(std::move(player));
	return true;
}

bool Turn::playerCanJoin(const std::string& player_name){
	for (auto it = this->players.begin(); it != this->players.end(); ++it){
		if (it->getName() == player_name){
			return false;
		}
	}
	return true;
}

size_t Turn::getPlayersSize() const{
	return this->players.size();
}

Player& Turn::getCurrentPlayer(){
	return this->players.at(this->current);
}

void Turn::beginTurn(){
	do {
		this->advanceCurrent();
	} while (this->getCurrentPlayer().isDead());
	this->getCurrentPlayer().beginTurn();
}

std::vector<Player>& Turn::getPlayers(){
	return this->players;
}

void Turn::advanceCurrent(){
	this->current++;
	if (this->current >= this->players.size()){
		this->current = 0;
	}
}

void Turn::addWorm(World& world, GameParameters& parameters, b2Vec2 position, int id){
	this->players[this->current].addWorm(world, parameters, position, id);
	this->advanceCurrent();
}

void Turn::distributeWorms(size_t size, int life_to_add){
	int quantity = (size / this->players.size());
	if (size % this->players.size() != 0){
		quantity += 1;
	}

	for (auto it = this->players.begin(); it != this->players.end(); ++it){
		it->distributeWorms(quantity, life_to_add);
	}
}

bool Turn::gameEnded(std::mutex& mutex){
	std::lock_guard<std::mutex> lock(mutex);
	this->winner.clear();
	size_t players_alive = 0;
	for (auto it = this->players.begin(); it != this->players.end(); ++it){
		if (!it->isDead()){
			players_alive++;
			this->winner = it->getName();
		}
	}
	///////////////////////////////////////////////return players_alive <= 1;
	if (this->players.size() == 1){
	return players_alive == 0;
	}else{return players_alive<=1;}////por ahora con un solo jugador
}

const std::string& Turn::getWinner(){
	return this->winner;
}
