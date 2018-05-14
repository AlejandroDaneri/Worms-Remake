#include "server_Banana.h"
#include "b2Fixture.h"
#include "b2CircleShape.h"

Banana::Banana(World& world, GameParameters& parameters):
	Weapon(world, parameters, parameters.get_banana_damage(), parameters.get_banana_radius()){}
		
Banana::~Banana(){}

std::string Banana::getName(){
	return BANANA_NAME;
}

void Banana::createFixtures(){
	b2CircleShape circleShape;
	circleShape.m_p.Set(0, 0);
	circleShape.m_radius = 0.5;
		  
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &circleShape;
	fixtureDef.density = 4;
	fixtureDef.restitution = 0.9; //rebotable
	this->body->CreateFixture(&fixtureDef);
}
