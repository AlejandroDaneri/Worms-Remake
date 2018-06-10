#include "FragmentableWeapon.h"
#include "WeaponFactory.h"
#include "Fragment.h"
#include "Math.h"
#include <string>

FragmentableWeapon::FragmentableWeapon(World& world, GameParameters& parameters,
													int damage, int fragments, int radius):
	Weapon(world, parameters, damage, radius), fragments(fragments){}

FragmentableWeapon::~FragmentableWeapon(){}

void FragmentableWeapon::explode(){
	WeaponFactory factory(this->world, this->parameters);
	for (float angle = 0; angle < 360; angle+= (360 / fragments)){
		physical_object_ptr fragment = factory.getWeapon(this->getName() + FRAGMENT);

		b2Vec2 center = this->body->GetPosition() +
						0.3 * b2Vec2(Math::cosDegrees(angle), Math::sinDegrees(angle));
		((Fragment *) fragment.get())->setShootPosition(center);
		((Fragment*)fragment.get())->shoot(angle);
		this->world.addWeaponFragment(fragment);
	}
	Weapon::explode();
}
