#include "GameParameters.h"
#include "ConfigFields.h"
#include <algorithm>
#include <random>

#define WORLD_MAX_HEIGHT "world_max_height"

GameParameters::GameParameters(const std::string& config_file, const std::string& config_editor_file){

	//Compruebo que existan todos los parametros necesarios
	YAML::Node config(YAML::LoadFile(config_file));
	YAML::Node config_editor(YAML::LoadFile(config_editor_file));

	this->float_parameters[DATA_SENDER_SLEEP] = config[DATA_SENDER_SLEEP].as<float>();
	this->float_parameters[GAME_WAITING_WORLD_SLEEP] = config[GAME_WAITING_WORLD_SLEEP].as<float>();
	this->float_parameters[WORLD_SLEEP_AFTER_STEP] = config[WORLD_SLEEP_AFTER_STEP].as<float>();
	this->float_parameters[WORLD_TIME_STEP] = config[WORLD_TIME_STEP].as<float>();

	this->float_parameters[WORMS_LIFE] = config_editor[WORMS_LIFE].as<float>();
	this->float_parameters[WORMS_LIFE_TO_ADD] = config[WORMS_LIFE_TO_ADD].as<float>();
	this->float_parameters[WORM_VELOCITY] = config[WORM_VELOCITY].as<float>();
	this->float_parameters[WORM_EXPLOSION_VELOCITY] = config[WORM_EXPLOSION_VELOCITY].as<float>();
	this->float_parameters[WORM_JUMP_VELOCITY] = config[WORM_JUMP_VELOCITY].as<float>();
	this->float_parameters[WORM_ROLLBACK_VELOCITY] = config[WORM_ROLLBACK_VELOCITY].as<float>();
	this->float_parameters[WORM_JUMP_HEIGHT] = config[WORM_JUMP_HEIGHT].as<float>();
	this->float_parameters[WORM_ROLLBACK_HEIGHT] = config[WORM_ROLLBACK_HEIGHT].as<float>();
	this->float_parameters[WORM_HEIGHT_TO_DAMAGE] = config[WORM_HEIGHT_TO_DAMAGE].as<float>();
	this->float_parameters[WORM_MAX_HEIGHT_DAMAGE] = config[WORM_MAX_HEIGHT_DAMAGE].as<float>();
	this->float_parameters[WEAPONS_VELOCITY] = config[WEAPONS_VELOCITY].as<float>();
	this->float_parameters[WIND_MIN_VELOCITY] = config[WIND_MIN_VELOCITY].as<float>();
	this->float_parameters[WIND_MAX_VELOCITY] = config[WIND_MAX_VELOCITY].as<float>();
	this->float_parameters[GRAVITY] = config[GRAVITY].as<float>();
	this->float_parameters[AIR_MISSILES_SEPARATION] = config[AIR_MISSILES_SEPARATION].as<float>();
	this->float_parameters[MAX_GIRDER_ROTATION_FRICTION] = config[MAX_GIRDER_ROTATION_FRICTION].as<float>();
	this->float_parameters[WORLD_MAX_HEIGHT] = 99999;

	this->weapon_radius = config[WEAPON_RADIUS].as<std::map<std::string, int>>();
	this->weapon_ammo = config_editor[WEAPON_AMMO].as<std::map<std::string, int>>();
	this->weapon_damage = config[WEAPON_DAMAGE].as<std::map<std::string, int>>();
	this->weapon_fragments = config[WEAPON_FRAGMENTS].as<std::map<std::string, int>>();

	std::vector<std::vector<float>> worms_file = config_editor[WORMS_DATA].as<std::vector<std::vector<float>>>();
	for (auto it = worms_file.begin(); it != worms_file.end(); ++it){
		this->worms.push_back(b2Vec2((*it)[0], (*it)[1]));
	}

	std::vector<std::vector<float>> girders_file = config_editor[GIRDERS_DATA].as<std::vector<std::vector<float>>>();
	for (auto it = girders_file.begin(); it != girders_file.end(); ++it){
		this->girders.push_back(GirderParams((*it)[0], (*it)[1], (*it)[2], (*it)[3]));
	}

	this->background_image = config_editor[BACKGROUND_IMAGE].as<std::string>();
}

GameParameters::~GameParameters(){}

int GameParameters::getWormLife(){
	return this->float_parameters[WORMS_LIFE];
}

int GameParameters::get_worms_life_to_add(){
	return this->float_parameters[WORMS_LIFE_TO_ADD];
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

std::map<std::string, int>& GameParameters::getWeaponsAmmo(){
	return this->weapon_ammo;
}

float GameParameters::getWormVelocity(){
	return this->float_parameters[WORM_VELOCITY];
}

float GameParameters::getWormExplosionVelocity(){
	return this->float_parameters[WORM_EXPLOSION_VELOCITY];
}

float GameParameters::getWormJumpVelocity(){
	return this->float_parameters[WORM_JUMP_VELOCITY];
}

float GameParameters::getWormRollbackVelocity(){
	return this->float_parameters[WORM_ROLLBACK_VELOCITY];
}

float GameParameters::getWormJumpHeight(){
	return this->float_parameters[WORM_JUMP_HEIGHT];
}

float GameParameters::getWormRollbackHeight(){
	return this->float_parameters[WORM_ROLLBACK_HEIGHT];
}

int GameParameters::getWormHeightToDamage(){
	return this->float_parameters[WORM_HEIGHT_TO_DAMAGE];
}

int GameParameters::getWormMaxHeightDamage(){
	return this->float_parameters[WORM_MAX_HEIGHT_DAMAGE];
}

float GameParameters::getWeaponsVelocity(){
	return this->float_parameters[WEAPONS_VELOCITY];
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
	return this->float_parameters[WIND_MIN_VELOCITY];
}

float GameParameters::getWindMaxVelocity(){
	return this->float_parameters[WIND_MAX_VELOCITY];
}

float GameParameters::getGravity(){
	return this->float_parameters[GRAVITY];
}

float GameParameters::getAirMissilesSeparation(){
	return this->float_parameters[AIR_MISSILES_SEPARATION];
}

int GameParameters::getMaxGirderRotationToFriction(){
	return this->float_parameters[MAX_GIRDER_ROTATION_FRICTION];
}

void GameParameters::setMaxHeight(int height){
	this->float_parameters[WORLD_MAX_HEIGHT] = height + 15;
}

int GameParameters::getMaxHeight(){
	return this->float_parameters[WORLD_MAX_HEIGHT];
}

int GameParameters::getDataSenderSleep(){
	return this->float_parameters[DATA_SENDER_SLEEP];
}

int GameParameters::getGameWaitingWorldSleep(){
	return this->float_parameters[GAME_WAITING_WORLD_SLEEP];
}

int GameParameters::getWorldSleepAfterStep(){
	return this->float_parameters[WORLD_SLEEP_AFTER_STEP];
}

float GameParameters::getWorldTimeStep(){
	return this->float_parameters[WORLD_TIME_STEP];
}

const std::string& GameParameters::getBackgroundImage(){
	return this->background_image;
}

GameParameters::GirderParams::GirderParams(size_t len, float pos_x, float pos_y, int rotation):
	len(len), pos_x(pos_x), pos_y(pos_y), rotation(rotation){}
