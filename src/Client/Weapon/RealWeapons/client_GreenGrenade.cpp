#include "client_GreenGrenade.h"
#include "client_Weapons_defs.h"

GreenGrenade::GreenGrenade(int ammo): DistanceWeapon(GREEN_GRENADE_NAME, ammo,
																	true) {}

GreenGrenade::~GreenGrenade(){}

GreenGrenade::GreenGrenade(GreenGrenade&& other) : DistanceWeapon(std::move(other)) {}

