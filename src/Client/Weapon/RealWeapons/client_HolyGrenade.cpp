#include "client_HolyGrenade.h"

HolyGrenade::HolyGrenade(int ammo) : DistanceWeapon(HOLY_GRENADE_NAME, ammo,
	HOLY_GRENADE_DAMAGE, HOLY_GRENADE_RADIUS, DEFAULT_TIME) {}

HolyGrenade::~HolyGrenade(){}

