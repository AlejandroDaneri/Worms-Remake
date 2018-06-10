#include "Scope.h"
#include "Path.h"
#include "WeaponNames.h"

Scope::Scope(WorldView& world) : world(world) {
	this->scope.set(SCOPE_IMAGE);
	this->angle = DEFAULT_ANGLE;
	this->world.addElement(this->scope, Position(0, 0), 0, 0);
}

Scope::~Scope() {}

void Scope::update(int angle, WormView& worm) {
	this->angle = angle;
	char dir = worm.getDir();
	if (dir == DIR_LEFT)
		angle = 180 - angle;
	this->world.moveScope(this->scope, worm.getWidget(), angle);
	this->scope.show();
	worm.updateScope(this->angle);
}

void Scope::update(WormView& worm) {
	this->update(this->angle, worm);
}


void Scope::hide() {
	if (this->scope.is_visible()) {
		this->scope.hide();
	}
}
