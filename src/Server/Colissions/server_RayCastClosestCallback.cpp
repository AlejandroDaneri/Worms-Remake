#include "RayCastClosestCallback.h"

RayCastClosestCallback::RayCastClosestCallback(): closest(NULL){}

RayCastClosestCallback::~RayCastClosestCallback(){}

b2Body* RayCastClosestCallback::getClosestBody(){
	return this->closest;
}

b2Vec2 RayCastClosestCallback::getClosestNormal(){
	return this->normal;
}


float32 RayCastClosestCallback::ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float32 fraction){
	this->closest = fixture->GetBody();
	this->normal = normal;
	return fraction;
}