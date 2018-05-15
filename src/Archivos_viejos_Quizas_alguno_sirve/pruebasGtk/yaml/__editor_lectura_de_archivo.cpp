#include "yaml-cpp/yaml.h"
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>


//LECTURA DE ARCHIVO YAML
int main(int argc, char* argv[]){

	YAML::Node config = YAML::LoadFile("./src/Archivos_viejos_Quizas_alguno_sirve/pruebasGtk/yaml/config_editor.yaml");

	int worms_life = config["worms_life"].as<int>();
	std::cout << "worms_life: " << worms_life << std::endl;

	//convierto directamente a map
	std::map<std::string, int> ammo = config["weapon_ammo"].as<std::map<std::string, int>>();

	std::cout << "En el map: ammo bazooka: " << ammo["Bazooka"] << std::endl;
	std::cout << "ammo dynamite: " << ammo["Dynamite"]<< std::endl;


	//convierto worms a vector
	std::vector<std::vector<int>> worms = config["worms"].as<std::vector<std::vector<int>>>();

	std::cout <<"\nworms:\n\n";
	for (auto it = worms.begin(); it != worms.end(); ++it){
		std::cout << "pos_x: " << (*it)[0] << " pos_y: " << (*it)[1] << std::endl;
	}

	//convierto girders a vector
	std::vector<std::vector<int>> girders = config["girders"].as<std::vector<std::vector<int>>>();

	std::cout <<"\nGirders:\n\n";
	for (auto it = girders.begin(); it != girders.end(); ++it){
		std::cout << "len: " << (*it)[0] <<"  pos_x: " << (*it)[1] << " pos_y: " << (*it)[2] << "  rotation: "<<(*it)[3] << std::endl;
	}

	return 0;
}