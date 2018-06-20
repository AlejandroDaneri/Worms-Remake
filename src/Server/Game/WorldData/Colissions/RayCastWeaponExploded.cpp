#include "RayCastWeaponExploded.h"
#include "Worm.h"

RayCastWeaponExploded::RayCastWeaponExploded(): closest(NULL){}

RayCastWeaponExploded::~RayCastWeaponExploded(){}

b2Body* RayCastWeaponExploded::getClosestWorm(){
	if (!this->closest){
		return NULL;
	}
	CollisionData* data = (CollisionData*)this->closest->GetUserData();
	if (data->getType() != TYPE_WORM){
		this->closest = NULL;
		return NULL;
	}

	this->affected_worms.push_back(this->closest);
	b2Body* closest_worm = this->closest;
	this->closest = NULL;
	return closest_worm;
}

float32 RayCastWeaponExploded::ReportFixture(b2Fixture* fixture,
						const b2Vec2& point, const b2Vec2& normal, float32 fraction){
	b2Body* closest_body = fixture->GetBody();
	for (b2Body* affected_worm: this->affected_worms){
		if (affected_worm == closest_body){
			return -1;
		}
	}
	this->closest = closest_body;
	return fraction;
}
