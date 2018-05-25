#include "AirAttack.h"
#include "WeaponFactory.h"
#include "Worm.h"

#define SEPARATION (weapon_size * 2)

AirAttack::AirAttack(World& world, GameParameters& parameters):
	Weapon(world, parameters, 0){}
		
AirAttack::~AirAttack(){}

const std::string& AirAttack::getName(){
	return AIR_ATTACK_NAME;
}

void AirAttack::shoot(char dir, int angle, int power, int time){}

void AirAttack::shoot(Worm& shooter, b2Vec2 pos){
	int missiles = this->parameters.getWeaponFragments(AIR_ATTACK_NAME);
	float pos_x = pos.x - missiles * SEPARATION / 2;
	float pos_y = this->parameters.getMaxHeight();
	WeaponFactory factory(this->world, this->parameters);
	for (int i = 0; i < missiles; i++, pos_x += SEPARATION){
		physical_object_ptr missile = factory.getWeapon(AIR_ATTACK_MISSILE_NAME);
		this->world.addObject(missile, b2Vec2(pos_x, pos_y));
	};
}