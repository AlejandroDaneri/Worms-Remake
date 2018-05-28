#include "PlayerDataSender.h"

PlayerDataSender::PlayerDataSender(Player& player): player(player){}

PlayerDataSender::~PlayerDataSender(){}

void PlayerDataSender::run(){
	while (true){
		std::unique_lock<std::mutex> lock(this->mutex);
		while (this->queue.empty() && this->running){
			this->condition_variable.wait(lock);
		}

		if (!this->running){
			break;
		}
		try{
            this->player.getProtocol().sendBuffer(this->queue.front());
			this->queue.pop();
		} catch(const SocketException& e){
			this->player.disconnect();
		}
	}
}

void PlayerDataSender::sendData(Buffer buffer){
	std::unique_lock<std::mutex> lock(this->mutex);
	this->queue.push(buffer);
}

void PlayerDataSender::notify(){
	this->condition_variable.notify_one();
}

void PlayerDataSender::stop(){
	Thread::stop();
	this->notify();
}
