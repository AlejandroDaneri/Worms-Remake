#include "FragmentableWeapon.h"
#include "WeaponFactory.h"
#include "Fragment.h"
#include "Math.h"

FragmentableWeapon::FragmentableWeapon(World& world, GameParameters& parameters, int damage, int fragments, int radius):
	Weapon(world, parameters, damage, radius), fragments(fragments){}

FragmentableWeapon::~FragmentableWeapon(){}

void FragmentableWeapon::explode(){
	WeaponFactory factory(this->world, this->parameters);
	for (float fragment_angle = 0; fragment_angle < 360; fragment_angle+= (360 / this->fragments)){
		physical_object_ptr fragment = factory.getWeapon(this->getName() + FRAGMENT);

		b2Vec2 center = this->body->GetPosition() + b2Vec2(Math::cosDegrees(fragment_angle),
														   Math::sinDegrees(fragment_angle));
		((Fragment*)fragment.get())->set_shoot_position(center);
		((Fragment*)fragment.get())->shoot(fragment_angle, this->time_to_explode);
		this->world.addWeaponFragment(fragment);
	}
	Weapon::explode();
}
