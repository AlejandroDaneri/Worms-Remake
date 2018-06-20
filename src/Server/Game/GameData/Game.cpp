#include "Game.h"
#include "Girder.h"
#include "WeaponFactory.h"
#include "Server.h"
#include <map>
#include <string>
#include <vector>

#define TURN_STEP 100 //milliseconds

Game::Game(size_t players, const std::string& config_file,
					const std::string& map, Server& server):
	players(players), server(server),
	parameters(config_file, map),
	world(this->parameters){
		this->running = true;
	}

Game::~Game(){
	this->world.stop();
	this->world.join();
	if (data_sender){
		this->data_sender->stop();
		this->data_sender->join();
	}
}

bool Game::addPlayer(Player& player){
	if (this->isFull()){
		return false;
	}

	return this->turn.addPlayer(player);
}

bool Game::isFull(){
	return this->players <= this->turn.getPlayersSize();
}

bool Game::playerCanJoin(const std::string& player_name){
	if (this->isFull()){
		return false;
	}
	return this->turn.playerCanJoin(player_name);
}

void Game::run(){
	this->configure();
	this->world.start();
	this->data_sender->start();

	std::this_thread::sleep_for(std::chrono::milliseconds(100));
	this->waitToWorld();

	while (!this->turn.gameEnded(this->world.getMutex())){
		this->player_turn_active = true;
		this->turn.beginTurn();
		int worm_id = this->turn.getCurrentPlayer().getCurrentWorm().getId();
		int player_id = this->turn.getCurrentPlayer().getId();
		this->data_sender->sendStartTurn(worm_id, player_id, this->world.getWind());

		size_t current_turn_time = 0;
		size_t max_turn_time = this->parameters.getTurnTime() * 1000;
		bool time_reduced = false;
		while(current_turn_time < max_turn_time){
			std::this_thread::sleep_for(std::chrono::milliseconds(TURN_STEP));
			current_turn_time += TURN_STEP;
			Worm& current_worm = this->turn.getCurrentPlayer().getCurrentWorm();
			if (current_worm.damageReceived() || this->turn.gameEnded(world.getMutex())){
				current_turn_time = max_turn_time;
			}else if (!time_reduced && current_worm.hasShot()){
				current_turn_time = max_turn_time - parameters.getTimeAfterShoot() * 1000;
				time_reduced = true;
			}
		}
		
		this->turn.endTurn();
		this->data_sender->sendEndTurn();
		this->waitToWorld();
		this->world.update();
	}
	std::this_thread::sleep_for(std::chrono::milliseconds(50));
	this->data_sender->sendEndGame(this->turn.getWinner());
	this->world.stop();
	this->data_sender->stop();
	this->data_sender->join();
	for (Player& player: this->turn.getPlayers()){
		if (player.isConnected()){
			this->server.addConnectedClient(std::move(player.getProtocol()));
		}
	}
	this->running = false;
}

void Game::configure(){
	DataSender* s = new DataSender(world, turn.getPlayers(), parameters);
	this->data_sender.reset(s);
	this->turn.startGame(*this->data_sender);

	this->data_sender->sendStartGame();
	this->data_sender->sendBackgroundImage(this->parameters.getBackgroundImage());
	int turn_time = this->parameters.getTurnTime();
	int time_after_shoot = this->parameters.getTimeAfterShoot();
	this->data_sender->sendTurnData(turn_time, time_after_shoot);
	this->data_sender->sendPlayersId();

	//Asignacion de gusanos
	std::vector<b2Vec2>& worms_list = this->parameters.getWorms();
	size_t size = worms_list.size();
	for (size_t i = 0; i < size; i++){
		this->turn.addWorm(this->world, this->parameters, worms_list[i], i);
	}
	this->turn.distributeWorms(size, this->parameters.getWormsLifeToAdd());

	//Creacion de vigas
	int max_height = 0;
	std::vector<GirderParams>& list = this->parameters.getGirders();
	size = list.size();
	for (size_t i = 0; i < size; i++){
		Girder* g = new Girder(world, parameters, list[i].len, list[i].rotation);
		physical_object_ptr girder(g);
		this->world.addObject(girder, b2Vec2(list[i].pos_x, list[i].pos_y));
		if (list[i].pos_y > max_height){
			max_height = list[i].pos_y;
		}
	}
	this->parameters.setMaxHeight(max_height);
	this->data_sender->sendGirders();

	//Municion de las armas
	std::map<std::string, unsigned int>& ammo = this->parameters.getWeaponsAmmo();
	this->data_sender->sendWeaponsAmmo(ammo);
	for (Player& player: this->turn.getPlayers()){
		player.setWeaponsAmmo(ammo);
	}
}

void Game::endTurn(){
	this->player_turn_active = false;
}

void Game::waitToWorld(){
	while (this->world.isActive() || this->data_sender->isActive()){
		int sleep = this->parameters.getGameWaitingWorldSleep();
		std::this_thread::sleep_for(std::chrono::milliseconds(sleep));
	}
}
