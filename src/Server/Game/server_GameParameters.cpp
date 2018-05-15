#include "GameParameters.h"
#include <algorithm>
#include <random>

GameParameters::GameParameters(const std::string& config_file, const std::string& config_editor):
	config(YAML::LoadFile(config_file)), config_editor(YAML::LoadFile(config_editor)){

	this->max_players = 1;

	for (int i = 0; i < 5; i++){
		//this->worms_list.push_back(b2Vec2(10 * (i+1), 60));
		this->girders_list.push_back(GirderParams(6, 10 * (i+1) - 3, 20, 0));
	}
}
	
GameParameters::~GameParameters(){}

int GameParameters::getWormLife(){
	return this->config_editor["worms_life"].as<int>();
}

int GameParameters::get_worms_life_to_add(){
	return this->config["worms_life_to_add"].as<int>();
}

#include <iostream>/////////////////
std::vector<b2Vec2> GameParameters::getWorms(){
	std::vector<b2Vec2> worms;
	std::vector<std::vector<int>> worms_file = config_editor["worms"].as<std::vector<std::vector<int>>>();

	for (auto it = worms_file.begin(); it != worms_file.end(); ++it){
		worms.push_back(b2Vec2((*it)[0], (*it)[1]));
	}


	std::random_device rd;
    std::mt19937 random(rd());
 
    //std::shuffle(worms.begin(), worms.end(), random);////////////////////////////////////////para probar cosas saco el random
	return worms;
}

std::vector<GirderParams>& GameParameters::getGirders(){
	return this->girders_list;//////////////////////////////////////////////////////
}

std::map<std::string, int> GameParameters::getWeaponsAmmo(){
	std::map<std::string, int> ammo = config_editor["weapon_ammo"].as<std::map<std::string, int>>();
	return ammo;
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
	return this->max_players;////////////////////////////////////////////////////////////////////////////////////
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
