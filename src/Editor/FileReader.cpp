

#include <iostream>
#include "FileReader.h"

FileReader::FileReader(const std::string &filename) : File(filename,
                                                           std::fstream::in) {}

void FileReader::read(std::vector<std::vector<double>>& worms,
                      std::vector<std::vector<double>>& girders,
                      std::vector<int>& weps_ammo) {
    YAML::Node config = YAML::LoadFile("config_editor.yaml");

  /*/
    int worms_life = config["worms_life"].as<int>();
    std::cout << "worms_life: " << worms_life << std::endl;
/*/

    //convierto directamente a map
    std::map<std::string, int> ammo = config[WEAPON_AMMO].as<std::map<std::string,
            int>>();

    weps_ammo.push_back(ammo[BAZOOKA_NAME]);
    weps_ammo.push_back(ammo[MORTAR_NAME]);
    weps_ammo.push_back(ammo[GREEN_GRENADE_NAME]);
    weps_ammo.push_back(ammo[RED_GRENADE_NAME]);
    weps_ammo.push_back(ammo[BANANA_NAME]);
    weps_ammo.push_back(ammo[AIR_ATTACK_NAME]);
    weps_ammo.push_back(ammo[BAT_NAME]);
    weps_ammo.push_back(ammo[DYNAMITE_NAME]);
    weps_ammo.push_back(ammo[HOLY_GRENADE_NAME]);
    std::cout << "ammo dynamite: " << ammo["Dynamite"]<< std::endl;

    //carga de  worms
    worms = config["worms"].as<std::vector<std::vector<double>>>();

    //carga de vigas
    girders = config["girders"].as<std::vector<std::vector<double>>>();

}
