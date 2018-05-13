#include "client_HolyGrenade.h"
#include "client_Weapons_defs.h"

HolyGrenade::HolyGrenade(int ammo) : DistanceWeapon(HOLY_GRENADE_NAME, ammo, 
																	true) {}

HolyGrenade::~HolyGrenade(){}

HolyGrenade::HolyGrenade(HolyGrenade&& other) : DistanceWeapon(std::move(other)) {}

