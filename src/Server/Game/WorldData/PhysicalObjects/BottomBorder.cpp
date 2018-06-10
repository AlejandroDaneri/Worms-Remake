#include "BottomBorder.h"
#include "b2PolygonShape.h"
#include "b2Fixture.h"

BottomBorder::BottomBorder(World& world):
	PhysicalObject(world, 0, TYPE_BORDER){}

BottomBorder::~BottomBorder(){}

void BottomBorder::getBodyDef(b2BodyDef& body_def, const b2Vec2& pos){
	body_def.type = b2_staticBody; 
	body_def.position.Set(pos.x, pos.y); 
}

void BottomBorder::createFixtures(){
	b2PolygonShape boxShape;
	boxShape.SetAsBox(100000,1);

	b2FixtureDef boxFixtureDef;
	boxFixtureDef.shape = &boxShape;
	boxFixtureDef.density = 1;
	this->body->CreateFixture(&boxFixtureDef);
}
