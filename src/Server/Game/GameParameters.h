#ifndef __GAMEPARAMETERS_H__
#define __GAMEPARAMETERS_H__

#include <string>
#include <vector>
#include <map>
#include "b2Math.h"

class GameParameters{
	public:
		class GirderParams;

	private:
		int worm_life;
		int worm_life_to_add;

		std::vector<b2Vec2> worms_list;
		std::vector<GirderParams> girders_list;


		float worm_velocity;
		float worm_jump_velocity;
		float worm_jump_height;
		float worm_rollback_height;
		float worm_rollback_velocity;

		float weapons_velocity;

		int bazooka_radius;
		int bazooka_damage;

		int banana_radius;
		int banana_damage;

		int redGrenade_radius;
		int redGrenade_damage;
		int redGrenade_fragments;

		int redGrenadeFragment_radius;
		int redGrenadeFragment_damage;

		int airAttack_missiles;
		int airAttack_radius;
		int airAttack_damage;

		size_t max_players;

	public:
		GameParameters(const std::string& config_file);
		~GameParameters();

		int getWormLife();
		int get_worms_life_to_add();

		std::vector<b2Vec2>& getWorms();
		std::vector<GirderParams>& getGirders();


		float getWormVelocity();
		float getWormJumpVelocity();
		float getWormRollbackVelocity();
		float getWormJumpHeight();
		float getWormRollbackHeight();

		float getWeaponsVelocity();

		int get_bazooka_radius();
		int get_bazooka_damage();

		int get_banana_radius();
		int get_banana_damage();

		int get_redGrenade_damage();
		int get_redGrenade_radius();
		int get_redGrenade_fragments();

		int get_redGrenadeFragment_damage();
		int get_redGrenadeFragment_radius();

		int get_airAttack_missiles();
		int get_airAttack_radius();
		int get_airAttack_damage();

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
