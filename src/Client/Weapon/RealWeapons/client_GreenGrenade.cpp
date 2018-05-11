#include "client_GreenGrenade.h"

GreenGrenade::GreenGrenade(int ammo): DistanceWeapon(GREEN_GRENADE_NAME, ammo,
	GREEN_GRENADE_DAMAGE, GREEN_GRENADE_RADIUS, DEFAULT_TIME) {}

GreenGrenade::~GreenGrenade(){}

