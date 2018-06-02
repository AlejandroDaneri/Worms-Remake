

#include "FileWriter.h"

FileWriter::FileWriter(const std::string &filename)
        : file(filename, std::fstream::out | std::ios_base::trunc) {}


void FileWriter::save(std::vector<int> weapons,
                      const std::vector<std::vector<double>> &worms,
                      const std::vector<std::vector<double>> &girders,
                      const unsigned int &worm_life, const std::string& background) {
    YAML::Emitter out;

    out << YAML::BeginMap;

    out << YAML::Key << BACKGROUND_IMAGE;
    out << YAML::Value << background;

    out << YAML::Key << WORMS_LIFE;
    out << YAML::Value << worm_life;

    out << YAML::Key << WEAPON_AMMO;

    out << YAML::Value << YAML::BeginMap;

    out << YAML::Key << BAZOOKA_NAME;
    out << YAML::Value << weapons[0];
    out << YAML::Key << MORTAR_NAME;
    out << YAML::Value << weapons[1];
    out << YAML::Key << GREEN_GRENADE_NAME;
    out << YAML::Value << weapons[2];
    out << YAML::Key << RED_GRENADE_NAME;
    out << YAML::Value << weapons[3];
    out << YAML::Key << BANANA_NAME;
    out << YAML::Value << weapons[4];
    out << YAML::Key << HOLY_GRENADE_NAME;
    out << YAML::Value << weapons[9];
    out << YAML::Key << DYNAMITE_NAME;
    out << YAML::Value << weapons[8];
    out << YAML::Key << BAT_NAME;
    out << YAML::Value << weapons[6];
    out << YAML::Key << AIR_ATTACK_NAME;
    out << YAML::Value << weapons[5];
    out << YAML::Key << TELEPORT_NAME;
    out << YAML::Value << weapons[7];

    out << YAML::EndMap;

    out << YAML::Key << WORMS_DATA;
    out << worms;

    out << YAML::Key << GIRDERS_DATA;
    out << girders;


    out << YAML::EndMap;

    file << out.c_str();
}