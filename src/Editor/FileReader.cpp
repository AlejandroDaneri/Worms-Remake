

#include "FileReader.h"

FileReader::FileReader(const std::string &filename) : File(filename,
                                                           std::fstream::in) {}

void FileReader::read(std::vector<std::vector<double>> &worms,std::vector<std::vector<double>> &girders) {
    YAML::Node config = YAML::LoadFile("config_editor.yaml");
  /*/
    int worms_life = config["worms_life"].as<int>();
    std::cout << "worms_life: " << worms_life << std::endl;

    //convierto directamente a map
    std::map<std::string, int> ammo = config["weapon_ammo"].as<std::map<std::string, int>>();

    std::cout << "En el map: ammo bazooka: " << ammo["Bazooka"] << std::endl;
    std::cout << "ammo dynamite: " << ammo["Dynamite"]<< std::endl;

/*/
    //carga de  worms
    worms = config["worms"].as<std::vector<std::vector<double>>>();

    //carga de vigas
    girders = config["girders"].as<std::vector<std::vector<double>>>();

}
