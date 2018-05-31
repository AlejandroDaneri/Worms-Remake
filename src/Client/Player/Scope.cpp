#include "Scope.h"
#include "Path.h"

const int DEFAULT_ANGLE = 48;

Scope::Scope(WorldView& world): world(world){
	this->in_world = false;
	this->scope.set(SCOPE_IMAGE);
	this->angle = DEFAULT_ANGLE;
}

Scope::~Scope(){}

void Scope::update(int angle, WormView& worm){
	this->angle = angle;
	if (!this->in_world){
		this->addScopeToWorld();
	}
	char dir = worm.getDir();
	if (dir == -1)
		angle = 180 - angle;
	this->world.moveScope(this->scope, worm.getWidget(), angle);
	this->scope.show();
	worm.updateScope(this->angle);
}

void Scope::update(WormView& worm){
	this->update(this->angle, worm);
}


void Scope::hide(){
	if (this->scope.is_visible()){
		this->scope.hide();
	}
}

void Scope::addScopeToWorld(){
	this->world.addElement(this->scope, Position(0,0), 0, 0);
	this->in_world = true;
}