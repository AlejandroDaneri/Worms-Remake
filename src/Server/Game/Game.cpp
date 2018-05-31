#include "Game.h"
#include "Girder.h"
#include "WeaponFactory.h"


Game::Game(size_t players, const std::string& config_file, const std::string& map):
	players(players), parameters(config_file, map), world(this->parameters){
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
	return this->players <= this->turn.get_players_size();
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
	this->wait_to_world();

	while (!this->turn.gameEnded(this->world.getMutex())){
		this->player_turn_active = true;
		this->turn.begin_turn();
		int worm_id = this->turn.getCurrentPlayer().getCurrentWorm().getId();
		int player_id = this->turn.getCurrentPlayer().getId();
		this->data_sender->send_start_turn(worm_id, player_id, this->world.getWind());

		while (this->player_turn_active){
			try{
				this->turn.getCurrentPlayer().getProtocol().receive(*this, *this->data_sender);
			} catch (const SocketException& e){
				this->player_turn_active = false;
				this->turn.getCurrentPlayer().disconnect();
			}
		}

		this->wait_to_world();
		this->world.update();
	}
	std::this_thread::sleep_for(std::chrono::milliseconds(50));
	this->data_sender->sendEndGame(this->turn.getWinner());
	this->world.stop();
	this->data_sender->stop();
	this->running = false;
}

void Game::configure(){
	this->data_sender.reset(new DataSender(this->world, this->turn.getPlayers(), this->parameters));

	this->data_sender->send_start_game();
	this->data_sender->sendBackgroundImage(this->parameters.getBackgroundImage());
	this->data_sender->send_players_id();

	//Asignacion de gusanos
	std::vector<b2Vec2>& worms_list = this->parameters.getWorms();
	size_t size = worms_list.size();
	for (size_t i = 0; i < size; i++){
		this->turn.addWorm(this->world, this->parameters, worms_list[i], i);
	}
	this->turn.distributeWorms(size, this->parameters.get_worms_life_to_add());

	//Creacion de vigas
	int max_height = 0;
	std::vector<GirderParams>& girders_list = this->parameters.getGirders();
	size = girders_list.size();
	for (size_t i = 0; i < size; i++){
		physical_object_ptr girder(new Girder(this->world, this->parameters, girders_list[i].len, girders_list[i].rotation));
		this->world.addObject(girder, b2Vec2(girders_list[i].pos_x, girders_list[i].pos_y));
		if (girders_list[i].pos_y > max_height){
			max_height = girders_list[i].pos_y;
		}
	}
	this->parameters.setMaxHeight(max_height);
	this->data_sender->sendGirders();

	//Municion de las armas
	std::map<std::string, int>& ammo = this->parameters.getWeaponsAmmo();
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
		std::this_thread::sleep_for(std::chrono::milliseconds(this->parameters.getGameWaitingWorldSleep()));
	}
}
