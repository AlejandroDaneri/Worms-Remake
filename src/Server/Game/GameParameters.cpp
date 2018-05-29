#include "GameParameters.h"
#include "ConfigFields.h"
#include <algorithm>
#include <random>

GameParameters::GameParameters(const std::string& config_file, const std::string& config_editor):
	config(YAML::LoadFile(config_file)), config_editor(YAML::LoadFile(config_editor)){
			
	this->world_max_height = 999999;
}

GameParameters::~GameParameters(){}

int GameParameters::getWormLife(){
	return this->config_editor[WORMS_LIFE].as<int>();
}

int GameParameters::get_worms_life_to_add(){
	return this->config[WORMS_LIFE_TO_ADD].as<int>();
}

std::vector<b2Vec2> GameParameters::getWorms(){
	std::vector<b2Vec2> worms;
	std::vector<std::vector<int>> worms_file = config_editor[WORMS_DATA].as<std::vector<std::vector<int>>>();

	for (auto it = worms_file.begin(); it != worms_file.end(); ++it){
		worms.push_back(b2Vec2((*it)[0], (*it)[1]));
	}

	std::random_device rd;
    std::mt19937 random(rd());
 
    std::shuffle(worms.begin(), worms.end(), random);
	return worms;
}

std::vector<GirderParams> GameParameters::getGirders(){
	std::vector<GirderParams> girders;
	std::vector<std::vector<int>> girders_file = config_editor[GIRDERS_DATA].as<std::vector<std::vector<int>>>();

	for (auto it = girders_file.begin(); it != girders_file.end(); ++it){
		girders.push_back(GirderParams((*it)[0], (*it)[1], (*it)[2], (*it)[3]));
	}
	return girders;
}

std::map<std::string, int> GameParameters::getWeaponsAmmo(){
	std::map<std::string, int> ammo = config_editor[WEAPON_AMMO].as<std::map<std::string, int>>();
	return ammo;
}

float GameParameters::getWormVelocity(){
	return this->config[WORM_VELOCITY].as<float>();
}

float GameParameters::getWormExplosionVelocity(){
	return this->config[WORM_EXPLOSION_VELOCITY].as<float>();
}

float GameParameters::getWormJumpVelocity(){
	return this->config[WORM_JUMP_VELOCITY].as<float>();
}

float GameParameters::getWormRollbackVelocity(){
	return this->config[WORM_ROLLBACK_VELOCITY].as<float>();
}

float GameParameters::getWormJumpHeight(){
	return this->config[WORM_JUMP_HEIGHT].as<float>();
}

float GameParameters::getWormRollbackHeight(){
	return this->config[WORM_ROLLBACK_HEIGHT].as<float>();
}

int GameParameters::getWormHeightToDamage(){
	return this->config[WORM_HEIGHT_TO_DAMAGE].as<int>();
}

int GameParameters::getWormMaxHeightDamage(){
	return this->config[WORM_MAX_HEIGHT_DAMAGE].as<int>();
}

float GameParameters::getWeaponsVelocity(){
	return this->config[WEAPONS_VELOCITY].as<float>();
}

int GameParameters::getWeaponDamage(const std::string& weapon){
	return this->config[WEAPON_DAMAGE][weapon].as<int>();
}

int GameParameters::getWeaponRadius(const std::string& weapon){
	return this->config[WEAPON_RADIUS][weapon].as<int>();
}

int GameParameters::getWeaponFragments(const std::string& weapon){
	return this->config[WEAPON_FRAGMENTS][weapon].as<int>();
}

float GameParameters::getWindMinVelocity(){
	return this->config[WIND_MIN_VELOCITY].as<float>();
}

float GameParameters::getWindMaxVelocity(){
	return this->config[WIND_MAX_VELOCITY].as<float>();
}

float GameParameters::getGravity(){
	return this->config[GRAVITY].as<float>();
}

float GameParameters::getAirMissilesSeparation(){
	return this->config[AIR_MISSILES_SEPARATION].as<float>();
}

int GameParameters::getMaxGirderRotationToFriction(){
	return this->config[MAX_GIRDER_ROTATION_FRICTION].as<int>();
}

void GameParameters::setMaxHeight(int height){
	this->world_max_height = height + 15;
}

int GameParameters::getMaxHeight(){
	return this->world_max_height;
}

GameParameters::GirderParams::GirderParams(size_t len, int pos_x, int pos_y, int rotation):
	len(len), pos_x(pos_x), pos_y(pos_y), rotation(rotation){}
