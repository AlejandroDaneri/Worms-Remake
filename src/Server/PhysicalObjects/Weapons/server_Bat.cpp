#include "server_Bat.h"

Bat::Bat(World& world, GameParameters& parameters):
	Weapon(world, parameters, parameters.getWeaponDamage(BAT_NAME), parameters.getWeaponRadius(BAT_NAME)){}
		
Bat::~Bat(){}

const std::string& Bat::getName(){
	return DYNAMITE_NAME;
}

void Bat::setInitialVelocity(){
	this->explode();
}

#include "Worm.h"
#include "math_utils.h"
void Bat::explode(){
	b2Vec2 center = this->body->GetPosition();
	b2Vec2 end = center + this->radius * b2Vec2(Math::cos_degrees(this->angle), Math::sin_degrees(this->angle));
	b2Vec2 normal;
	b2Body* closest_body = this->world.getClosestObject(center, end, normal);
	if (closest_body){
		CollisionData* data = (CollisionData*)closest_body->GetUserData();
		if (data->getType() == TYPE_WORM){
			Worm* worm = ((Worm*)data->getObject());
			float distance = b2Distance(center, worm->getPosition());
			int worm_damage = this->damage * (1 - distance / (2 * this->radius)); //Justo en el borde hace la mitad de danio
			worm->receive_weapon_damage(worm_damage, normal, this->id);
		}
	}

	this->waiting_to_explode = false;
	this->is_dead = true;
}
