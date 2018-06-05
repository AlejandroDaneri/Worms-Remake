#include "DataReceiver.h"
#include "Player.h"
#include <glibmm/main.h>
#include "ObjectSizes.h"

DataReceiver::DataReceiver(Player& player): 
	player(player), protocol(player.getProtocol()){}

DataReceiver::~DataReceiver(){
	this->protocol.stop();
}

void DataReceiver::run(){
	try{
		this->initialConfig();
		while(this->running){
			Buffer data = this->protocol.receiveBuffer();
			sigc::slot<bool> my_slot = sigc::bind(sigc::mem_fun(*this, &DataReceiver::analizeReceivedData), data);
			Glib::signal_idle().connect(my_slot);
		}

	} catch (const std::exception& e){
		if (this->running){
			this->player.getScreen().close();
		}
	}
}

void DataReceiver::initialConfig(){
	this->protocol.receiveStartGame();
	this->protocol.receiveBackgroundImage(this->player.getScreen().getWorld());
	this->protocol.receivePlayers(this->player.getScreen().getPlayersView());
	this->protocol.receiveGirders(this->player.getViewsList());
	this->protocol.receiveWeaponsAmmo(this->player.getWeapons());
	this->player.getScreen().show();
}

bool DataReceiver::analizeReceivedData(Buffer buffer){
	char action = buffer.getNext();

	if (action == START_TURN){
		int worm_id = Protocol::receiveIntBuffer(buffer);
		int player_id = Protocol::receiveIntBuffer(buffer);
		float wind = Protocol::receiveIntBuffer(buffer) / UNIT_TO_SEND;
		this->player.startTurn(worm_id, player_id, wind);
	} else if (action == END_GAME){
		std::string winner = Protocol::receiveStringBuffer(buffer);
		this->player.endGame(winner);
	} else if (action == END_TURN){
		this->player.endTurnEarly();
	} else if (action == CHANGE_WEAPON_ACTION) {
		std::string weapon(Protocol::receiveStringBuffer(buffer));
		this->player.getViewsList().removeScopeVisibility();
		this->player.getViewsList().changeWeapon(weapon);
	} else if (action == MOVE_SCOPE) {
		int angle = Protocol::receiveIntBuffer(buffer);
		this->player.getViewsList().updateScope(angle);
	} else if (action == SHOOT_WEAPON_ACTION) {
		std::string weapon(Protocol::receiveStringBuffer(buffer));
		this->player.getViewsList().removeScopeVisibility();
		this->player.getViewsList().shoot(weapon);
		this->player.getMusicPlayer().playWeaponShotSound(weapon);
	} else if (action == MOVING_OBJECT) {
		char type = buffer.getNext();
		int id = Protocol::receiveIntBuffer(buffer);

		if (type == WORM_TYPE){
			int player_id = Protocol::receiveIntBuffer(buffer);
			int pos_x = Protocol::receiveIntBuffer(buffer);
			int pos_y = Protocol::receiveIntBuffer(buffer);
			int life = Protocol::receiveIntBuffer(buffer);
			char dir = buffer.getNext();
			bool colliding = buffer.getNext();
			this->player.getViewsList().updateWormData(id, player_id, pos_x, pos_y, life, dir, colliding);
			this->player.getViewsList().removeScopeVisibility();
		} else if (type == WEAPON_TYPE){
			std::string weapon(Protocol::receiveStringBuffer(buffer));

			int pos_x = Protocol::receiveIntBuffer(buffer);
			int pos_y = Protocol::receiveIntBuffer(buffer);
			this->player.getViewsList().updateWeaponData(id, weapon, pos_x, pos_y);
		}
	} else if (action == DEAD_OBJECT){
		char type = buffer.getNext();
		int id = Protocol::receiveIntBuffer(buffer);
		if (type == WORM_TYPE){
			this->player.getViewsList().removeWorm(id);
		} else if (type == WEAPON_TYPE){
			this->player.getViewsList().removeWeapon(id);
		}
	} else if (action == MOVE_ACTION){
		char movement = buffer.getNext();
		this->player.getMusicPlayer().playJumpSound(movement);
	}
	return false;
}
