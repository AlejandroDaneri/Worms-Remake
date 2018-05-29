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

	public:
		GameParameters(const std::string& config_file, const std::string& config_editor_file);
		~GameParameters();

		int getWormLife();
		int get_worms_life_to_add();

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
};

class GameParameters::GirderParams{
	public:
		size_t len;
		int pos_x;
		int pos_y;
		int rotation;

		GirderParams(size_t len, int pos_x, int pos_y, int rotation);
};

typedef GameParameters::GirderParams GirderParams;

#endif
