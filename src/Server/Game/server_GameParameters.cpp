#include "GameParameters.h"
#include <algorithm>
#include <random>

GameParameters::GameParameters(const std::string& config_file): config(YAML::LoadFile(config_file)){
	//leer el archivo  YAML y cargar las variables

	this->worm_life = 125;

	this->max_players = 1;

	for (int i = 0; i < 5; i++){
		this->worms_list.push_back(b2Vec2(10 * (i+1), 60));
		this->girders_list.push_back(GirderParams(6, 10 * (i+1) - 3, 20, 0));
	}

	this->weapons_ammo["Bazooka"] =  99999;
	this->weapons_ammo["Mortar"] =  10;
	this->weapons_ammo["GreenGrenade"] =  99999;
	this->weapons_ammo["RedGrenade"] =  10;
	this->weapons_ammo["Banana"] =  5;
	this->weapons_ammo["HolyGrenade"] =  2;
	this->weapons_ammo["Dynamite"] =  5;
	this->weapons_ammo["Bat"] =  99999;
	this->weapons_ammo["AirAttack"] =  2;
	this->weapons_ammo["Teleportation"] =  99999;
}
	
GameParameters::~GameParameters(){}

int GameParameters::getWormLife(){
	return this->worm_life;////////////////////////////////////////////////
}

int GameParameters::get_worms_life_to_add(){
	return this->config["worms_life_to_add"].as<int>();
}

std::vector<b2Vec2>& GameParameters::getWorms(){
	std::random_device rd;
    std::mt19937 random(rd());
 
    std::shuffle(this->worms_list.begin(), this->worms_list.end(), random);////////////////////////////////////////
	return this->worms_list;
}

std::vector<GirderParams>& GameParameters::getGirders(){
	return this->girders_list;//////////////////////////////////////////////////////
}

std::map<std::string, int>& GameParameters::getWeaponsAmmo(){
	return this->weapons_ammo;////////////////////////////////////////////////
}

float GameParameters::getWormVelocity(){
	return this->config["worm_velocity"].as<float>();
}

float GameParameters::getWormJumpVelocity(){
	return this->config["worm_jump_velocity"].as<float>();
}

float GameParameters::getWormRollbackVelocity(){
	return this->config["worm_rollback_velocity"].as<float>();
}

float GameParameters::getWormJumpHeight(){
	return this->config["worm_jump_height"].as<float>();
}

float GameParameters::getWormRollbackHeight(){
	return this->config["worm_rollback_height"].as<float>();
}

float GameParameters::getWeaponsVelocity(){
	return this->config["weapons_velocity"].as<float>();
}

size_t GameParameters::get_max_players(){
	return this->max_players;/////////////////////////////////////////////////////////////////////////
}

int GameParameters::getWeaponDamage(std::string weapon){
	return this->config["weapon_damage"][weapon].as<int>();
}

int GameParameters::getWeaponRadius(std::string weapon){
	return this->config["weapon_radius"][weapon].as<int>();
}

int GameParameters::getWeaponFragments(std::string weapon){
	return this->config["weapon_fragments"][weapon].as<int>();
}

GameParameters::GirderParams::GirderParams(size_t len, int pos_x, int pos_y, int rotation):
	len(len), pos_x(pos_x), pos_y(pos_y), rotation(rotation){}
