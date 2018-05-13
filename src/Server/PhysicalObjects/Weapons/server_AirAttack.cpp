#include "server_AirAttack.h"
#include "server_WeaponFactory.h"
#include "Worm.h"

#define SKY 60
#define SEPARATION 2

AirAttack::AirAttack(World& world, GameParameters& parameters):
	Weapon(world, parameters, 0){}
		
AirAttack::~AirAttack(){}

std::string AirAttack::getName(){
	return "AirAttack";
}

void AirAttack::shoot(char dir, int angle, int power, int time){}

void AirAttack::shoot(Worm& shooter, b2Vec2 pos){
	int missiles = this->parameters.get_airAttack_missiles();
	int pos_x = pos.x - missiles * SEPARATION / 2;
	WeaponFactory factory(this->world, this->parameters);
	for (int i = 0; i < missiles; i++, pos_x += SEPARATION){
		physical_object_ptr missile = factory.getWeapon("AirAttackMissile");
		this->world.addObject(missile, b2Vec2(pos_x, SKY));
	};
}
