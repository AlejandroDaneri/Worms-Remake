#include "GameParameters.h"

GameParameters::GameParameters(const std::string& config_file){
	//leer el archivo  YAML y cargar las variables

	this->worm_life = 125;
	this->worm_velocity = 3.2;
	this->worm_jump_velocity = 7;
	this->worm_rollback_velocity = 7;
	this->worm_jump_height = 7;
	this->worm_rollback_height = 7;
	this->bazooka_radius = 2;
	this->bazooka_damage = 50;
	this->max_players = 1;
	this->weapons_velocity = 13;

	this->redGrenade_radius = 2;
	this->redGrenade_damage = 30;
	this->redGrenade_fragments = 6;

	this->redGrenadeFragment_radius = 2;
	this->redGrenadeFragment_damage = 10;
}
		
GameParameters::~GameParameters(){}

int GameParameters::getWormLife(){
	return this->worm_life;
}

float GameParameters::getWormVelocity(){
	return this->worm_velocity;
}

float GameParameters::getWormJumpVelocity(){
	return this->worm_jump_velocity;
}

float GameParameters::getWormRollbackVelocity(){
	return this->worm_rollback_velocity;
}

float GameParameters::getWormJumpHeight(){
	return this->worm_jump_height;
}

float GameParameters::getWormRollbackHeight(){
	return this->worm_rollback_height;
}

float GameParameters::getWeaponsVelocity(){
	return this->weapons_velocity;
}

int GameParameters::get_bazooka_radius(){
	return this->bazooka_radius;
}

int GameParameters::get_bazooka_damage(){
	return this->bazooka_damage;
}

int GameParameters::get_redGrenade_radius(){
	return this->redGrenade_radius;
}

int GameParameters::get_redGrenade_damage(){
	return this->redGrenade_damage;
}

int GameParameters::get_redGrenadeFragment_radius(){
	return this->redGrenadeFragment_radius;
}

int GameParameters::get_redGrenadeFragment_damage(){
	return this->redGrenadeFragment_damage;
}

int GameParameters::get_redGrenade_fragments(){
	return this->redGrenade_fragments;
}

size_t GameParameters::get_max_players(){
	return this->max_players;
}