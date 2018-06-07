#include "DataSender.h"

DataSender::DataSender(World& world, std::vector<Player>& players, GameParameters& parameters): 
	objects(world.getObjectsList()), girders(world.getGirdersList()), 
	players(players), mutex(world.getMutex()), active(false), sleep_time(parameters.getDataSenderSleep()){

		for (size_t i = 0; i < this->players.size(); i++){
			std::unique_ptr<PlayerDataSender> sender(new PlayerDataSender(this->players[i]));
			this->players_data_senders.push_back(std::move(sender));
			this->players_data_senders[i]->start();
		}
	}

DataSender::~DataSender(){
	for (size_t i = 0; i < this->players.size(); i++){
		this->players_data_senders[i]->stop();
		this->players_data_senders[i]->join();
	}
}

void DataSender::run(){
	while(this->running){
		std::this_thread::sleep_for(std::chrono::milliseconds(this->sleep_time));
		std::lock_guard<std::mutex> lock(this->mutex);
		this->active = false;
		auto it = this->objects.begin();

		while(it != this->objects.end()){
			if ((*it)->isDead() && !(*it)->getBody()){
				Buffer data = ServerProtocol::sendDeadObject(*it);

				this->sendBuffer(data);
				it = this->objects.erase(it);
				continue;
			}

			if ((*it)->isMoving()){
				Buffer data = ServerProtocol::sendObject(*it);
				this->sendBuffer(data);
				this->active = true;
			}
			++it;
		}

		if (!this->active){
			//Chequeo que no se hayan desconectado
			Buffer empty_data;
			empty_data.setNext(NO_SEND_DATA);
			this->sendBuffer(empty_data);
		}

		this->notifyAll();
		this->checkPlayers();
	}
}

void DataSender::sendBackgroundImage(File& image){
	Buffer data = ServerProtocol::sendFile(image);
	this->sendBuffer(data);
	this->notifyAll();
}

void DataSender::sendStartGame(){
	Buffer data = ServerProtocol::sendStartGame();
	this->sendBuffer(data);
	this->notifyAll();
}

void DataSender::sendPlayersId(){
	Buffer length = ServerProtocol::sendLengthBuffer(this->players.size());
	this->sendBuffer(length);
	for (auto it = this->players.begin(); it != this->players.end(); ++it){
		Buffer data = ServerProtocol::sendPlayerId(*it);
		this->sendBuffer(data);
	}
    this->notifyAll();
}

void DataSender::sendGirders(){
	Buffer length = ServerProtocol::sendLengthBuffer(this->girders.size());
	this->sendBuffer(length);
	for (auto it = this->girders.begin(); it != this->girders.end(); ++it){
		Buffer data = ServerProtocol::sendGirder(*it);
		this->sendBuffer(data);
	}
    this->notifyAll();
}

void DataSender::sendWeaponsAmmo(std::map<std::string, int>& weapons){
	Buffer length = ServerProtocol::sendLengthBuffer(weapons.size());
	this->sendBuffer(length);
	for (auto it = weapons.begin(); it != weapons.end(); ++it){
		Buffer data = ServerProtocol::sendWeaponAmmo(it->first, it->second);
		this->sendBuffer(data);
	}
    this->notifyAll();
}

void DataSender::sendStartTurn(int worm_id, int player_id, float wind){
	Buffer data = ServerProtocol::sendStartTurn(worm_id, player_id, wind);
	this->sendBuffer(data);
	this->notifyAll();
}

void DataSender::sendWeaponChanged(const std::string &weapon){
	Buffer data = ServerProtocol::sendWeaponChanged(weapon);
	this->sendBuffer(data);
	this->notifyAll();
}

void DataSender::sendWeaponShot(const std::string& weapon){
	Buffer data = ServerProtocol::sendWeaponShot(weapon);
	this->sendBuffer(data);
	this->notifyAll();
}

void DataSender::sendMoveAction(char action){
	if (action == MOVE_RIGHT || action == MOVE_LEFT){
		return;
	}
	Buffer data = ServerProtocol::sendMoveAction(action);
	this->sendBuffer(data);
	this->notifyAll();
}

void DataSender::sendUpdateScope(int angle) {
	Buffer data = ServerProtocol::sendUpdateScope(angle);
	this->sendBuffer(data);
	this->notifyAll();
}

void DataSender::sendEndGame(const std::string& winner){
	Buffer data = ServerProtocol::sendEndGame(winner);
	this->sendBuffer(data);
	this->notifyAll();
}

void DataSender::sendEndTurn(){
	Buffer data = this->players[0].getProtocol().sendEndTurn();
	this->sendBuffer(data);
	this->notifyAll();
}

bool DataSender::isActive(){
	std::lock_guard<std::mutex> lock(this->mutex);
	return this->active;
}

void DataSender::sendBuffer(const Buffer& buffer){
	for (size_t i = 0; i < this->players.size(); i++){
		if (this->players[i].isConnected()){
			this->players_data_senders[i]->sendData(buffer);
		}
	}
}

void DataSender::notifyAll(){
	for (size_t i = 0; i < this->players.size(); i++){
		if (this->players[i].isConnected()){
			this->players_data_senders[i]->notify();
		}
	}
}

void DataSender::checkPlayers(){
	size_t players_connected = 0;
	for (size_t i = 0; i < this->players.size(); i++){
		if (this->players[i].isConnected()){
			players_connected++;
		}
	}
	if (players_connected <= 1 && this->players.size() > 1){ //////////////////////////////Eliminar playersize>1 por ahora que hay un solo jugador
		Buffer data = this->players[0].getProtocol().sendEndTurn();
		this->sendBuffer(data);
		this->notifyAll();
	}
}
