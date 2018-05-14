#include "yaml-cpp/yaml.h"
#include <iostream>
#include <fstream>
#include <string>
#include <map>


//LECTURA DE ARCHIVO YAML
int main(int argc, char* argv[]){

	YAML::Node config = YAML::LoadFile("./src/Archivos_viejos_Quizas_alguno_sirve/pruebasGtk/yaml/server_config.yaml");

	int worms_life = config["worms_life_to_add"].as<int>();
	std::cout << "worms_life_to_add: " << worms_life << std::endl;

	std::string bazooka = "Bazooka";
	std::string dynamite = "Dynamite";

	int bazooka_radius = config["weapon_radius"][bazooka].as<int>();
	int dynamite_radius = config["weapon_radius"][dynamite].as<int>();

	//convierto directamente a map
	std::map<std::string, int> radius = config["weapon_radius"].as<std::map<std::string, int>>();

	std::cout <<  bazooka_radius << std::endl;
	std::cout <<  dynamite_radius << std::endl;

	std::cout << "En el map: radio bazooka: " << radius["Bazooka"] << std::endl;
	std::cout << "radio dynamite: " << radius["Dynamite"]<< std::endl;

	return 0;
}