#ifndef __GAMEPARAMETERS_H__
#define __GAMEPARAMETERS_H__

#include <string>
#include <vector>
#include <map>
#include "b2Math.h"
#include "yaml.h"

class GameParameters{
	public:
		class GirderParams;

	private:
		std::map<std::string, float> float_parameters;
		std::map<std::string, int> weapon_radius;
		std::map<std::string, int> weapon_ammo;
		std::map<std::string, int> weapon_damage;
		std::map<std::string, int> weapon_fragments;

		std::vector<b2Vec2> worms;
		std::vector<GirderParams> girders;
		std::string background_image;

	public:
		//Inicializa todos los parametros necesarios para la partida
		GameParameters(const std::string& config_file, const std::string& config_editor_file);
		~GameParameters();

		int getWormLife();
		int getWormsLifeToAdd();

		std::vector<b2Vec2>& getWorms();
		std::vector<GirderParams>& getGirders();
		std::map<std::string, int>& getWeaponsAmmo();


		float getWormVelocity();
		float getWormExplosionVelocity();
		float getWormJumpVelocity();
		float getWormRollbackVelocity();
		float getWormJumpHeight();
		float getWormRollbackHeight();

		int getWormHeightToDamage();
		int getWormMaxHeightDamage();

		float getWeaponsVelocity();

		int getWeaponDamage(const std::string& weapon);
		int getWeaponRadius(const std::string& weapon);
		int getWeaponFragments(const std::string& weapon);

		float getWindMinVelocity();
		float getWindMaxVelocity();
		float getGravity();
		float getAirMissilesSeparation();

		int getMaxGirderRotationToFriction();
		void setMaxHeight(int height);
		int getMaxHeight();

		int getDataSenderSleep();
		int getGameWaitingWorldSleep();
		int getWorldSleepAfterStep();
		float getWorldTimeStep();

		const std::string& getBackgroundImage();
};

class GameParameters::GirderParams{
	public:
		size_t len;
		float pos_x;
		float pos_y;
		int rotation;

		GirderParams(size_t len, float pos_x, float pos_y, int rotation);
};

typedef GameParameters::GirderParams GirderParams;

#endif
