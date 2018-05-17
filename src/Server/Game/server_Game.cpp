#include "Game.h"
#include "Girder.h"
#include "server_WeaponFactory.h"


Game::Game(size_t players, const std::string& config_file, const std::string& config_editor):
	players(players), parameters(config_file, config_editor), world(this->parameters){}

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
	return this->players <= this->turn.get_players_size();
}


#include <iostream>/////////////////////////////////
void Game::run(){
	this->configure();
	this->world.start();
	this->data_sender->start();

	std::this_thread::sleep_for(std::chrono::milliseconds(100));
	this->wait_to_world();

/* PARA CUANDO ESTE IMPLEMENTADO EN EL CLIENTE LOS SEND*/
	while (!this->turn.gameEnded()){
		std::cout <<"empezo el juego\n";
		this->player_turn_active = true;
		this->turn.begin_turn();
		int worm_id = this->turn.getCurrentPlayer().getCurrentWorm().getId();
		int player_id = this->turn.getCurrentPlayer().getId();
		this->data_sender->send_start_turn(worm_id, player_id);

		while (this->player_turn_active){
			this->turn.getCurrentPlayer().getProtocol().receive(*this);
		}

		this->wait_to_world();

	}
//*/


	//PARA PROBAR COSAS
	/////////////////////////////////////////////////////////
	//sleep(5);
	//this->getCurrentWorm().changeWeapon("RedGrenade");
	//this->getCurrentWorm().shoot(60, 1000, -1);
	//this->getCurrentWorm().changeWeapon("AirAttack");
	//this->getCurrentWorm().shoot(b2Vec2(20, 50));
	////////////////////////////////////////////////////////
}

void Game::configure(){
	this->data_sender.reset(new DataSender(this->world, this->turn.getPlayers()));

	this->data_sender->send_players_id();

	//Asignacion de gusanos
	std::vector<b2Vec2> worms_list = this->parameters.getWorms();
	size_t size = worms_list.size();
	for (size_t i = 0; i < size; i++){
		this->turn.addWorm(this->world, this->parameters, worms_list[i], i);
	}
	this->turn.distributeWorms(size, this->parameters.get_worms_life_to_add());

	//Creacion de vigas
	std::vector<GirderParams> girders_list = this->parameters.getGirders();
	size = girders_list.size();
	for (size_t i = 0; i < size; i++){
		physical_object_ptr girder(new Girder(this->world, girders_list[i].len, girders_list[i].rotation));
		this->world.addObject(girder, b2Vec2(girders_list[i].pos_x, girders_list[i].pos_y));
	}
	this->data_sender->sendGirders();

	//Municion de las armas
	std::map<std::string, int> ammo = this->parameters.getWeaponsAmmo();
	this->data_sender->sendWeaponsAmmo(ammo);
}

Worm& Game::getCurrentWorm(){
	return this->turn.getCurrentPlayer().getCurrentWorm();
}

void Game::endTurn(){
	this->player_turn_active = false;
}

void Game::wait_to_world(){
	while (this->world.isActive() || this->data_sender->isActive()){
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
}
