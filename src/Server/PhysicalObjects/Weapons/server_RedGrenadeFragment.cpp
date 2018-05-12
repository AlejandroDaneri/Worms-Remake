#include "server_RedGrenadeFragment.h"

RedGrenadeFragment::RedGrenadeFragment(World& world, GameParameters& parameters):
	Fragment(world, parameters, parameters.get_redGrenadeFragment_damage(), parameters.get_redGrenadeFragment_radius()){}
		
RedGrenadeFragment::~RedGrenadeFragment(){}

std::string RedGrenadeFragment::getName(){
	return "RedGrenade";
}