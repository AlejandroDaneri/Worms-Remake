#include "FragmentableWeapon.h"
#include "server_WeaponFactory.h"
#include "server_Fragment.h"
#include "math_utils.h"

FragmentableWeapon::FragmentableWeapon(World& world, GameParameters& parameters, int damage, int fragments, int radius):
	Weapon(world, parameters, damage, radius), fragments(fragments){}

FragmentableWeapon::~FragmentableWeapon(){}

void FragmentableWeapon::explode(){
	WeaponFactory factory(this->world, this->parameters);
	for (float fragment_angle = 0; fragment_angle < 360; fragment_angle+= (360 / this->fragments)){
		physical_object_ptr fragment = factory.getWeapon(this->getName() + FRAGMENT);

		b2Vec2 center = this->body->GetPosition() + b2Vec2(Math::cos_degrees(fragment_angle), Math::sin_degrees(fragment_angle));
		((Fragment*)fragment.get())->set_shoot_position(center);
		((Fragment*)fragment.get())->shoot(fragment_angle, this->time_to_explode);
		this->world.addWeaponFragment(fragment);
	}
	Weapon::explode();
}
