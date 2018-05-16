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

		size_t max_players;/////////////////////////////////////

	public:
		GameParameters(const std::string& config_file, const std::string& config_editor);
		~GameParameters();

		int getWormLife();
		int get_worms_life_to_add();

		std::vector<b2Vec2> getWorms();
		std::vector<GirderParams> getGirders();
		std::map<std::string, int> getWeaponsAmmo();


		float getWormVelocity();
		float getWormJumpVelocity();
		float getWormRollbackVelocity();
		float getWormJumpHeight();
		float getWormRollbackHeight();

		float getWeaponsVelocity();

		int getWeaponDamage(const std::string& weapon);
		int getWeaponRadius(const std::string& weapon);
		int getWeaponFragments(const std::string& weapon);

		size_t get_max_players();

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
