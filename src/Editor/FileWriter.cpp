
#include <yaml.h>
#include <iostream>
#include "FileWriter.h"
#include "MapObject.h"

FileWriter::FileWriter(const std::string &filename)
        : File(filename, std::fstream::out | std::ios_base::trunc) {}


void FileWriter::save(const std::vector<int>& weapons,
                std::vector<std::vector<double>>& worms,
                std::vector<std::vector<double>>& girders) {
    YAML::Emitter out;

    out << YAML::BeginMap;

    out << YAML::Key << "worms_life";
    out << YAML::Value << 200;

    //armas
    out << YAML::Key << "weapon_ammo";
    out << YAML::Value << YAML::BeginMap;
    out << YAML::Key << "Bazooka";
    out << YAML::Value << weapons[0];
    out << YAML::Key << "Mortar";
    out << YAML::Value << weapons[1];
    out << YAML::Key << "GreenGrenade";
    out << YAML::Value << weapons[2];
    out << YAML::Key << "RedGrenade";
    out << YAML::Value << weapons[3];
    out << YAML::Key << "Banana";
    out << YAML::Value << weapons[4];
    out << YAML::Key << "HolyGrenade";
    out << YAML::Value << weapons[9];
    out << YAML::Key << "Dynamite";
    out << YAML::Value << weapons[8];
    out << YAML::Key << "Bat";
    out << YAML::Value << weapons[6];
    out << YAML::Key << "AirAttack";
    out << YAML::Value << weapons[5];
    out << YAML::Key << "Teleportation";
    out << YAML::Value << weapons[7];

    out << YAML::EndMap;

    //posicion de gusanos
    out << YAML::Key << "worms";
    out << worms;

    out << YAML::Key << "girders";
    out << girders;


    out << YAML::EndMap;

    std::cout << "Here's the output YAML:\n\n\n" << out.c_str()<<std::endl;

    file << out.c_str();
}