#include "GameParameters.h"

GameParameters::GameParameters(const std::string& config_file){
	//leer el archivo  YAML y cargar las variables

	this->bazooka_radius = 2;
	this->bazooka_damage = 50;
	this->max_players = 1;
}
		
GameParameters::~GameParameters(){}

int GameParameters::get_bazooka_radius(){
	return this->bazooka_radius;
}

int GameParameters::get_bazooka_damage(){
	return this->bazooka_damage;
}

size_t GameParameters::get_max_players(){
	return this->max_players;
}