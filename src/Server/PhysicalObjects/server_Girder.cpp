#include "Girder.h"
#include "b2PolygonShape.h"
#include "b2Fixture.h"

Girder::Girder(World& world, size_t size, int rotation):
	PhysicalObject(world, 0, TYPE_GIRDER), size(size), rotation(rotation){}

Girder::~Girder(){}

void Girder::getBodyDef(b2BodyDef& body_def, const b2Vec2& pos){
	body_def.type = b2_staticBody; 
	body_def.position.Set(pos.x, pos.y); 
}

void Girder::createFixtures(){
	b2PolygonShape boxShape;
	boxShape.SetAsBox(this->size / 2.0, girder_height / 2);

	b2FixtureDef boxFixtureDef;
	boxFixtureDef.shape = &boxShape;
	boxFixtureDef.density = 1;
	this->body->CreateFixture(&boxFixtureDef);
}

size_t Girder::getSize(){
	return this->size;
}

int Girder::getRotation(){
	return this->rotation;
}

/////////////////////////////////////////////////////////////////////////////rotation
