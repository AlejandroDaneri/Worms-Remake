#include "Worm.h"
#include "b2PolygonShape.h"
#include "b2Fixture.h"
#include "Protocol.h"

Worm::Worm(World& world, int id, GameParameters& parameters):
	PhysicalObject(world, id, "Worm"), life(parameters.getWormLife()), 
	dir(0), parameters(parameters){}

Worm::~Worm(){}

void Worm::getBodyDef(b2BodyDef& body_def, const b2Vec2& pos){
	body_def.type = b2_dynamicBody;
	body_def.position.Set(pos.x, pos.y);
	body_def.fixedRotation = true;
}

void Worm::createFixtures(){
	b2PolygonShape boxShape;
	boxShape.SetAsBox(1,1);
		  
	b2FixtureDef boxFixtureDef;
	boxFixtureDef.shape = &boxShape;
	boxFixtureDef.density = 4;
	this->body->CreateFixture(&boxFixtureDef);
}

int Worm::getLife(){
	return this->life;
}

char Worm::getDir(){
	return this->dir;
}

void Worm::move(char action){
	if (action == MOVE_RIGHT){
		this->dir = action;
		b2Vec2 velocity(parameters.getWormVelocity(), 0);
		this->world.setLinearVelocity(*this, velocity);

	} else if (action == MOVE_LEFT){
		this->dir = action;
		b2Vec2 velocity(-1 * parameters.getWormVelocity(), 0);
		this->world.setLinearVelocity(*this, velocity);
	} else if (action == JUMP){
		b2Vec2 velocity(parameters.getWormJumpVelocity(), parameters.getWormJumpHeight());
		if (this->dir == MOVE_LEFT){
			velocity.x *= -1;
		}
		this->world.setLinearVelocity(*this, velocity);
	} else if (action == ROLLBACK){
		b2Vec2 velocity(parameters.getWormRollbackVelocity(), parameters.getWormRollbackHeight());
		if (this->dir == MOVE_RIGHT){
			velocity.x *= -1;
		}
		this->world.setLinearVelocity(*this, velocity);
	}
}

void Worm::changeWeapon(const std::string& weapon){
	///////////////////////////////////////////////////////////
}

void Worm::shoot(int angle, int power, int time){
	////////////////////////////////////////////////////////
}

void Worm::shoot(b2Vec2 pos){
	///////////////////////////////////////////////////
}

void Worm::collide_with_something(CollisionData* other){
	if (other->getType() == "Border"){
		this->life = 0;
		this->is_dead = true;
	}
}
