#include "client_WeaponsFactory.h"
#include "WeaponNames.h"

#include "client_AirAttack.h"
#include "client_Banana.h"
#include "client_Bat.h"
#include "client_Bazooka.h"
#include "client_Dynamite.h"
#include "client_GreenGrenade.h"
#include "client_HolyGrenade.h"
#include "client_Mortar.h"
#include "client_RedGrenade.h"
#include "client_Teleportation.h"


WeaponsFactory::WeaponsFactory() {}

WeaponsFactory::~WeaponsFactory() {}
		
weapon_ptr WeaponsFactory::create_weapon(std::string weapon, int ammo) {
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
