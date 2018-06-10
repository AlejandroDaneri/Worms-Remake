#include "MortarFragment.h"
#include <string>

MortarFragment::MortarFragment(World& world, GameParameters& parameters):
	Fragment(world, parameters,
		parameters.getWeaponDamage(MORTAR_FRAGMENTS_NAME),
		parameters.getWeaponRadius(MORTAR_FRAGMENTS_NAME)){}
		
MortarFragment::~MortarFragment(){}

const std::string& MortarFragment::getName(){
	return MORTAR_FRAGMENTS_NAME;
}

bool MortarFragment::isWindAffected(){
	return true;
}
