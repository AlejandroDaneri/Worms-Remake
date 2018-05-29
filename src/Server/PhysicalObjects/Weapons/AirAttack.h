#ifndef __SERVERAIRATTACK_H__
#define __SERVERAIRATTACK_H__

#include "Weapon.h"

class AirAttack: public Weapon{
	private:
		float missiles_separation;
		
	public:

		AirAttack(World& world, GameParameters& parameters);
		~AirAttack();

		const std::string& getName() override;

		void shoot(char dir, int angle, int power, int time) override;

		void shoot(Worm& shooter, b2Vec2 pos) override;

};

#endif
