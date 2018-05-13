#include "client_WeaponsFactory.h"
#include "client_Weapons_defs.h"

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
		
Weapon&& WeaponsFactory::create_weapon(std::string weapon, int ammo) {
	if (weapon == AIR_ATTACK_NAME)	
		return std::move(AirAttack(ammo));
	else if (weapon == BANANA_NAME)
		return std::move(Banana(ammo));
	else if (weapon == BAT_NAME)
		return std::move(Bat(ammo));
	else if (weapon == BAZOOKA_NAME)
		return std::move(Bazooka(ammo));
	else if (weapon == DYNAMITE_NAME)
		return std::move(Dynamite(ammo));
	else if (weapon == GREEN_GRENADE_NAME)
		return std::move(GreenGrenade(ammo));
	else if (weapon == HOLY_GRENADE_NAME)
		return std::move(HolyGrenade(ammo));
	else if (weapon == MORTAR_NAME)
		return std::move(Mortar(ammo));
	else if (weapon == RED_GRENADE_NAME)
		return std::move(RedGrenade(ammo));
	return std::move(Teleportation(ammo));
}
