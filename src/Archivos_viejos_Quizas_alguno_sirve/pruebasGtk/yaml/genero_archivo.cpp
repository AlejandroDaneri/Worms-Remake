#include "yaml-cpp/yaml.h"
#include <iostream>
#include <fstream>


//GENERACION DE ARCHIVO YAML
int main(int argc, char* argv[]){

	YAML::Emitter out;

	out << YAML::BeginMap;
	out << YAML::Key << "worms_life";
	out << YAML::Value << 200;
	out << YAML::Key << "worms_life_to_add";
	out << YAML::Value << 25;

	//radio de armas
	out << YAML::Key << "weapon_radius";
	out << YAML::Value << YAML::BeginMap;
	out << YAML::Key << "Bazooka";
	out << YAML::Value << 2;
	out << YAML::Key << "Dynamite";
	out << YAML::Value << 5;
	out << YAML::EndMap;

	//danio de armas
	out << YAML::Key << "weapon_damage";
	out << YAML::Value << YAML::BeginMap;
	out << YAML::Key << "Bazooka";
	out << YAML::Value << 50;
	out << YAML::Key << "Dynamite";
	out << YAML::Value << 45;
	out << YAML::EndMap;

	out << YAML::EndMap;

	std::cout << "Here's the output YAML:\n\n\n" << out.c_str()<<std::endl;

	//lo guardo en un archivo
	std::ofstream file("./src/Archivos_viejos_Quizas_alguno_sirve/pruebasGtk/yaml/yaml.txt");
	file << out.c_str();

	return 0;
}