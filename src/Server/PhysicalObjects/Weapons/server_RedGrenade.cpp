#include "server_RedGrenade.h"

RedGrenade::RedGrenade(World& world, GameParameters& parameters):
        FragmentableWeapon(world, parameters, parameters.get_redGrenade_damage(), parameters.get_redGrenade_fragments(), parameters.get_redGrenade_radius()){}

RedGrenade::~RedGrenade(){}

std::string RedGrenade::getName(){
        return RED_GRENADE_NAME;
}
