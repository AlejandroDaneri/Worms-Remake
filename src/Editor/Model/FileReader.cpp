
#include "FileReader.h"
#include <map>
#include <string>
#include <vector>

FileReader::FileReader(const std::string &filename):
    file(filename, std::fstream::in),
    filename(filename) {}

void FileReader::read(std::vector<std::vector<double>> &worms,
                      std::vector<std::vector<double>> &girders,
                      std::vector<int> &weps_ammo,
                      unsigned int &worms_life, std::string& background) {
    YAML::Node config = YAML::LoadFile(filename);

    background = config[BACKGROUND_IMAGE].as<std::string>();

    worms_life = config[WORMS_LIFE].as<unsigned int>();

    std::map<std::string, int> ammo =
                    config[WEAPON_AMMO].as<std::map<std::string, int>>();

    weps_ammo.push_back(ammo[BAZOOKA_NAME]);
    weps_ammo.push_back(ammo[MORTAR_NAME]);
    weps_ammo.push_back(ammo[GREEN_GRENADE_NAME]);
    weps_ammo.push_back(ammo[RED_GRENADE_NAME]);
    weps_ammo.push_back(ammo[BANANA_NAME]);
    weps_ammo.push_back(ammo[AIR_ATTACK_NAME]);
    weps_ammo.push_back(ammo[BAT_NAME]);
    weps_ammo.push_back(ammo[TELEPORT_NAME]);
    weps_ammo.push_back(ammo[DYNAMITE_NAME]);
    weps_ammo.push_back(ammo[HOLY_GRENADE_NAME]);

    worms = config[WORMS_DATA].as<std::vector<std::vector<double>>>();

    girders = config[GIRDERS_DATA].as<std::vector<std::vector<double>>>();
}
