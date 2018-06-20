#include "GameParameters.h"
#include "ConfigFields.h"
#include "Path.h"
#include <algorithm>
#include <random>
#include <map>
#include <string>
#include <vector>

#define WORLD_MAX_HEIGHT "world_max_height"

typedef std::vector<std::vector<float>> worms_vector;
typedef std::vector<std::vector<float>> girders_vector;

GameParameters::GameParameters(const std::string& config_file,
							const std::string& config_editor_file){
	//Compruebo que existan todos los parametros necesarios
	YAML::Node config(YAML::LoadFile(config_file));
	YAML::Node config_editor(YAML::LoadFile(config_editor_file));

	params[DATA_SENDER_SLEEP] = config[DATA_SENDER_SLEEP].as<float>();
	params[GAME_WAIT_WORLD_SLEEP] = config[GAME_WAIT_WORLD_SLEEP].as<float>();
	params[WORLD_SLEEP_AFTER_STEP] = config[WORLD_SLEEP_AFTER_STEP].as<float>();
	params[WORLD_TIME_STEP] = config[WORLD_TIME_STEP].as<float>();
	params[TURN_TIME] = config[TURN_TIME].as<float>();
	params[TIME_AFTER_SHOOT] = config[TIME_AFTER_SHOOT].as<float>();

	params[WORMS_LIFE] = config_editor[WORMS_LIFE].as<float>();
	params[WORMS_LIFE_TO_ADD] = config[WORMS_LIFE_TO_ADD].as<float>();
	params[WORM_VELOCITY] = config[WORM_VELOCITY].as<float>();
	params[WORM_EXPLOSION_VELOCITY] = config[WORM_EXPLOSION_VELOCITY].as<float>();
	params[WORM_JUMP_VELOCITY] = config[WORM_JUMP_VELOCITY].as<float>();
	params[WORM_ROLLBACK_VELOCITY] = config[WORM_ROLLBACK_VELOCITY].as<float>();
	params[WORM_JUMP_HEIGHT] = config[WORM_JUMP_HEIGHT].as<float>();
	params[WORM_ROLLBACK_HEIGHT] = config[WORM_ROLLBACK_HEIGHT].as<float>();
	params[WORM_HEIGHT_TO_DAMAGE] = config[WORM_HEIGHT_TO_DAMAGE].as<float>();
	params[WORM_MAX_HEIGHT_DAMAGE] = config[WORM_MAX_HEIGHT_DAMAGE].as<float>();
	params[WEAPONS_VELOCITY] = config[WEAPONS_VELOCITY].as<float>();
	params[WIND_MIN_VELOCITY] = config[WIND_MIN_VELOCITY].as<float>();
	params[WIND_MAX_VELOCITY] = config[WIND_MAX_VELOCITY].as<float>();
	params[GRAVITY] = config[GRAVITY].as<float>();
	params[AIR_MISSILES_SEPARATION] = config[AIR_MISSILES_SEPARATION].as<float>();
	params[GIRDER_ANGLE_FRICTION] = config[GIRDER_ANGLE_FRICTION].as<float>();
	params[WORLD_MAX_HEIGHT] = 99999;

	weapon_radius = config[WEAPON_RADIUS].as<std::map<std::string, int>>();
	weapon_ammo = 
				config_editor[WEAPON_AMMO].as<std::map<std::string, unsigned int>>();
	weapon_damage = config[WEAPON_DAMAGE].as<std::map<std::string, int>>();
	weapon_fragments = config[WEAPON_FRAGMENTS].as<std::map<std::string, int>>();

	worms_vector worms_file = config_editor[WORMS_DATA].as<worms_vector>();
	for (std::vector<float>& worm: worms_file){
		this->worms.push_back(b2Vec2(worm[0], worm[1]));
	}

	girders_vector girders_file = config_editor[GIRDERS_DATA].as<girders_vector>();
	for (std::vector<float>& girder: girders_file){
		this->girders.push_back(GirderParams(girder[0], girder[1], girder[2], girder[3]));
	}
		
	std::vector<int> bg = config_editor[BACKGROUND_IMAGE].as<std::vector<int>>();
    Buffer buffer(bg.size());
    for (int byte: bg){
		buffer.setNext(byte);
	}
	this->background_image = std::move(buffer);
}

GameParameters::~GameParameters(){}

int GameParameters::getWormLife(){
	return this->params[WORMS_LIFE];
}

int GameParameters::getWormsLifeToAdd(){
	return this->params[WORMS_LIFE_TO_ADD];
}

std::vector<b2Vec2>& GameParameters::getWorms(){
	std::random_device rd;
    std::mt19937 random(rd());
 
    std::shuffle(this->worms.begin(), this->worms.end(), random);
	return this->worms;
}

std::vector<GirderParams>& GameParameters::getGirders(){
	return this->girders;
}

std::map<std::string, unsigned int>& GameParameters::getWeaponsAmmo(){
	return this->weapon_ammo;
}

float GameParameters::getWormVelocity(){
	return this->params[WORM_VELOCITY];
}

float GameParameters::getWormExplosionVelocity(){
	return this->params[WORM_EXPLOSION_VELOCITY];
}

float GameParameters::getWormJumpVelocity(){
	return this->params[WORM_JUMP_VELOCITY];
}

float GameParameters::getWormRollbackVelocity(){
	return this->params[WORM_ROLLBACK_VELOCITY];
}

float GameParameters::getWormJumpHeight(){
	return this->params[WORM_JUMP_HEIGHT];
}

float GameParameters::getWormRollbackHeight(){
	return this->params[WORM_ROLLBACK_HEIGHT];
}

int GameParameters::getWormHeightToDamage(){
	return this->params[WORM_HEIGHT_TO_DAMAGE];
}

int GameParameters::getWormMaxHeightDamage(){
	return this->params[WORM_MAX_HEIGHT_DAMAGE];
}

float GameParameters::getWeaponsVelocity(){
	return this->params[WEAPONS_VELOCITY];
}

int GameParameters::getWeaponDamage(const std::string& weapon){
	return this->weapon_damage[weapon];
}

int GameParameters::getWeaponRadius(const std::string& weapon){
	return this->weapon_radius[weapon];
}

int GameParameters::getWeaponFragments(const std::string& weapon){
	return this->weapon_fragments[weapon];
}

float GameParameters::getWindMinVelocity(){
	return this->params[WIND_MIN_VELOCITY];
}

float GameParameters::getWindMaxVelocity(){
	return this->params[WIND_MAX_VELOCITY];
}

float GameParameters::getGravity(){
	return this->params[GRAVITY];
}

float GameParameters::getAirMissilesSeparation(){
	return this->params[AIR_MISSILES_SEPARATION];
}

int GameParameters::getMaxGirderRotationToFriction(){
	return this->params[GIRDER_ANGLE_FRICTION];
}

void GameParameters::setMaxHeight(int height){
	this->params[WORLD_MAX_HEIGHT] = height + 10;
}

int GameParameters::getMaxHeight(){
	return this->params[WORLD_MAX_HEIGHT];
}

int GameParameters::getDataSenderSleep(){
	return this->params[DATA_SENDER_SLEEP];
}

int GameParameters::getGameWaitingWorldSleep(){
	return this->params[GAME_WAIT_WORLD_SLEEP];
}

int GameParameters::getWorldSleepAfterStep(){
	return this->params[WORLD_SLEEP_AFTER_STEP];
}

float GameParameters::getWorldTimeStep(){
	return this->params[WORLD_TIME_STEP];
}

int GameParameters::getTurnTime(){
	return this->params[TURN_TIME];
}

int GameParameters::getTimeAfterShoot(){
	return this->params[TIME_AFTER_SHOOT];
}

Buffer& GameParameters::getBackgroundImage(){
	return this->background_image;
}

GameParameters::GirderParams::GirderParams(size_t len, float pos_x,
													float pos_y, int rotation):
	len(len), pos_x(pos_x), pos_y(pos_y), rotation(rotation){}
