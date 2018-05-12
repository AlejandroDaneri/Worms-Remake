#ifndef __GAMEPARAMETERS_H__
#define __GAMEPARAMETERS_H__

#include <string>

class GameParameters{
	private:
		int worm_life;
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

		size_t max_players;

	public:
		GameParameters(const std::string& config_file);
		~GameParameters();

		int getWormLife();
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

		size_t get_max_players();

};

#endif
