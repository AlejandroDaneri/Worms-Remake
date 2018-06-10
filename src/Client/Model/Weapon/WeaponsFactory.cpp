#include "WeaponsFactory.h"
#include "WeaponNames.h"
#include <string>
#include "AirAttack.h"
#include "Banana.h"
#include "Bat.h"
#include "Bazooka.h"
#include "Dynamite.h"
#include "GreenGrenade.h"
#include "HolyGrenade.h"
#include "Mortar.h"
#include "RedGrenade.h"
#include "Teleportation.h"


WeaponsFactory::WeaponsFactory() {}

WeaponsFactory::~WeaponsFactory() {}

weapon_ptr WeaponsFactory::createWeapon(std::string weapon, int ammo) {
	if (weapon == AIR_ATTACK_NAME)
		return weapon_ptr(new AirAttack(ammo));
	else if (weapon == BANANA_NAME)
		return weapon_ptr(new Banana(ammo));
	else if (weapon == BAT_NAME)
		return weapon_ptr(new Bat(ammo));
	else if (weapon == BAZOOKA_NAME)
		return weapon_ptr(new Bazooka(ammo));
	else if (weapon == DYNAMITE_NAME)
		return weapon_ptr(new Dynamite(ammo));
	else if (weapon == GREEN_GRENADE_NAME)
		return weapon_ptr(new GreenGrenade(ammo));
	else if (weapon == HOLY_GRENADE_NAME)
		return weapon_ptr(new HolyGrenade(ammo));
	else if (weapon == MORTAR_NAME)
		return weapon_ptr(new Mortar(ammo));
	else if (weapon == RED_GRENADE_NAME)
		return weapon_ptr(new RedGrenade(ammo));
	return weapon_ptr(new Teleportation(ammo));
}
