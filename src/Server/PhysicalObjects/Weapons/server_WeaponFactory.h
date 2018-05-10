#ifndef __WEAPONFACTORY_H__
#define __WEAPONFACTORY_H__

#include "World.h"
#include "GameParameters.h"
#include "server_Bazooka.h"

class WeaponFactory{
	private:
		World& world;
		GameParameters& parameters;

	public:
		WeaponFactory(World& world, GameParameters& parameters);
		~WeaponFactory();

		physical_object_ptr getWeapon(const std::string& name);

};

#endif
