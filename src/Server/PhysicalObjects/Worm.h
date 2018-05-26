#ifndef __WORM_H__
#define __WORM_H__

#include "PhysicalObject.h"
#include "GameParameters.h"
#include "Weapon.h"

class Worm: public PhysicalObject{	
	private:
		int player_id;
		int life;
		char dir;
		GameParameters& parameters;
		physical_object_ptr weapon;
		float max_height;
		int colliding_with_girder;
		int friction;

	protected:
		void getBodyDef(b2BodyDef& body_def, const b2Vec2& pos) override;
		void createFixtures() override;

	public:
		Worm(World& world, GameParameters& parameters, int id, int player_id);
		~Worm();

		int getPlayerId() const;
		int getLife() const;
		char getDir() const;
		bool isColliding() const;

		void addLife(int life);

		void reduce_life(int damage);

		void move(char action);

		void changeWeapon(const std::string& weapon);

		void shoot(int angle, int power, int time);

		void shoot(b2Vec2 pos);

		void collide_with_something(CollisionData* other) override;

		void end_collission_girder(char friction);

		void receive_weapon_damage(int damage, const b2Vec2& epicenter);

		bool isActive() override;
};

#endif
