#include "yaml-cpp/yaml.h"
#include <iostream>
#include <fstream>
#include <string>

int main(int argc, char* argv[]){

	YAML::Node config = YAML::LoadFile("./src/Archivos_viejos_Quizas_alguno_sirve/pruebasGtk/yaml/yaml.txt");

	int worms_life = config["worms_life"].as<int>();

	std::string bazooka = "Bazooka";
	std::string dynamite = "Dynamite";

	int bazooka_radius = config["weapon_radius"][bazooka].as<int>();
	int dynamite_radius = config["weapon_radius"][dynamite].as<int>();

	std::cout <<  worms_life << std::endl;
	std::cout <<  bazooka_radius << std::endl;
	std::cout <<  dynamite_radius << std::endl;

	return 0;
}