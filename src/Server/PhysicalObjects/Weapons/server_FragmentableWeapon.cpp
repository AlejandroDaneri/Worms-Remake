#include "FragmentableWeapon.h"
#include "server_WeaponFactory.h"
#include "server_Fragment.h"
#include <cmath>

#define PI 3.14159265
#define RADIANS PI / 180

FragmentableWeapon::FragmentableWeapon(World& world, GameParameters& parameters, int damage, int fragments, int radius):
	Weapon(world, parameters, damage, radius), fragments(fragments){}

FragmentableWeapon::~FragmentableWeapon(){}

void FragmentableWeapon::explode(){
	for (int fragment_angle = 0; fragment_angle < 360; fragment_angle+= (360 / this->fragments)){
		WeaponFactory factory(this->world, this->parameters);
		physical_object_ptr fragment = factory.getWeapon(this->getName() + "Fragment");

		b2Vec2 center = this->body->GetPosition() + 2 * b2Vec2(cos(fragment_angle * RADIANS), sin(fragment_angle * RADIANS));
		((Fragment*)fragment.get())->set_shoot_position(center);
		((Fragment*)fragment.get())->shoot(fragment_angle, this->time_to_explode);
		this->world.addWeaponFragment(fragment);
	}
	Weapon::explode();
}