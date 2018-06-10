#include "CollisionData.h"
#include "PhysicalObject.h"
#include <string>

CollisionData::CollisionData(std::string type, PhysicalObject* object):
	type(type), object(object){}

CollisionData::~CollisionData(){}

const std::string& CollisionData::getType(){
	return this->type;
}
		
PhysicalObject* CollisionData::getObject(){
	return this->object;
}
