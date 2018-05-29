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
		YAML::Node config;
		YAML::Node config_editor;

		int world_max_height;

	public:
		GameParameters(const std::string& config_file, const std::string& config_editor);
		~GameParameters();

		int getWormLife();
		int get_worms_life_to_add();

		std::vector<b2Vec2> getWorms();
		std::vector<GirderParams> getGirders();
		std::map<std::string, int> getWeaponsAmmo();


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
