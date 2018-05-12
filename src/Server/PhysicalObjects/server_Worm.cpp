#include "Worm.h"
#include "b2PolygonShape.h"
#include "b2Fixture.h"
#include "Protocol.h"
#include "server_WeaponFactory.h"

Worm::Worm(World& world, int id, GameParameters& parameters):
	PhysicalObject(world, id, "Worm"), life(parameters.getWormLife()), 
	dir(1), parameters(parameters), last_weapon_exploded(-1){}

Worm::~Worm(){}

void Worm::getBodyDef(b2BodyDef& body_def, const b2Vec2& pos){
	body_def.type = b2_dynamicBody;
	body_def.position.Set(pos.x, pos.y);
	body_def.fixedRotation = true;
}

void Worm::createFixtures(){
	b2PolygonShape boxShape;
	boxShape.SetAsBox(0.5, 0.5);
		  
	b2FixtureDef boxFixtureDef;
	boxFixtureDef.shape = &boxShape;
	boxFixtureDef.density = 1;
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
		velocity.x *= this->dir;
		this->world.setLinearVelocity(*this, velocity);
	} else if (action == ROLLBACK){
		b2Vec2 velocity(parameters.getWormRollbackVelocity(), parameters.getWormRollbackHeight());
		velocity.x *= -1 * this->dir;
		this->world.setLinearVelocity(*this, velocity);
	}
}

void Worm::changeWeapon(const std::string& weapon){
	WeaponFactory factory(this->world, this->parameters);
	this->weapon = factory.getWeapon(weapon);
}

void Worm::shoot(int angle, int power, int time){
	((Weapon*)this->weapon.get())->shoot(this->dir, angle, power, time);
	b2Vec2 pos = this->getPosition();
	pos.x += 2 * this->dir;
	this->world.addObject(this->weapon, pos);
}

void Worm::shoot(b2Vec2 pos){
	((Weapon*)this->weapon.get())->shoot(*this, pos);
	this->world.addObject(this->weapon, this->getPosition());
}

#include <iostream>/////////////////////////////////////
void Worm::receive_weapon_damage(int damage, const b2Vec2& normal, int weapon_id){
	if (weapon_id != this->last_weapon_exploded){
		this->life -= damage;
		std::cout <<"Danio worm id: "<<this->getId()<<" damage: "<<damage<<"  life: "<<this->life<<std::endl;
		std::cout <<"normal: "<<normal.x<<"  "<<normal.y<<std::endl;
		this->body->SetLinearVelocity(-1 * damage * normal);
		this->last_weapon_exploded = weapon_id;
		if (this->life <= 0){
			this->is_dead = true;
		}
	}
}

void Worm::collide_with_something(CollisionData* other){
	if (other->getType() == "Border"){
		this->life = 0;
		this->is_dead = true;
	}
	///////////////////////////falta para las vigas
}
