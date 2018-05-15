#include "yaml-cpp/yaml.h"
#include <iostream>
#include <fstream>
#include <vector>


//GENERACION DE ARCHIVO YAML
int main(int argc, char* argv[]){

	//genero los gusanos
	std::vector<std::vector<int>> worms;
	for (int i = 0; i < 5; i++){
		std::vector<int> position;
		position.push_back(10 * (i+1)); //pos x
		position.push_back(60); //pos_y
		worms.push_back(position);
	}

	//genero las vigas
	std::vector<std::vector<int>> girders;
	for (int i = 0; i < 5; i++){
		std::vector<int> data;
		data.push_back(6); //len
		data.push_back(10 * (i+1) - 3); //pos_x
		data.push_back(20); //pos_y
		data.push_back(0); //rotation
		girders.push_back(data);
	}

	YAML::Emitter out;

	out << YAML::BeginMap;

	out << YAML::Key << "worms_life";
	out << YAML::Value << 200;

	//radio de armas
	out << YAML::Key << "weapon_ammo";
	out << YAML::Value << YAML::BeginMap;
	out << YAML::Key << "Bazooka";
	out << YAML::Value << 99999;
	out << YAML::Key << "Mortar";
	out << YAML::Value << 10;
	out << YAML::Key << "GreenGrenade";
	out << YAML::Value << 99999;
	out << YAML::Key << "RedGrenade";
	out << YAML::Value << 10;
	out << YAML::Key << "Banana";
	out << YAML::Value << 5;
	out << YAML::Key << "HolyGrenade";
	out << YAML::Value << 2;
	out << YAML::Key << "Dynamite";
	out << YAML::Value << 5;
	out << YAML::Key << "Bat";
	out << YAML::Value << 99999;
	out << YAML::Key << "AirAttack";
	out << YAML::Value << 2;
	out << YAML::Key << "Teleportation";
	out << YAML::Value << 99999;

	out << YAML::EndMap;

	//posicion de gusanos
	out << YAML::Key << "worms";
	out << worms;

	out << YAML::Key << "girders";
	out << girders;

	/*out << YAML::Value << YAML::BeginSeq;

	out << YAML::Value << YAML::BeginSeq << 50 << 100 << YAML::EndSeq;
	out << YAML::Value << YAML::BeginSeq << 60 << 100 << YAML::EndSeq;
	out << YAML::Value << YAML::BeginSeq << 70 << 100 << YAML::EndSeq;
	
	out << YAML::EndSeq;*/


	out << YAML::EndMap;

	std::cout << "Here's the output YAML:\n\n\n" << out.c_str()<<std::endl;

	//lo guardo en un archivo
	std::ofstream file("./src/Archivos_viejos_Quizas_alguno_sirve/pruebasGtk/yaml/config_editor.yaml");
	file << out.c_str();

	return 0;
}