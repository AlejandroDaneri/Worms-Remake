#include "Wind.h"
#include <random>

Wind::Wind(GameParameters& parameters): 
	min_velocity(parameters.getWindMinVelocity()),
	max_velocity(parameters.getWindMaxVelocity()){
		this->update();
	}

Wind::~Wind(){}

float Wind::getVelocity() const{
	return this->velocity;
}

void Wind::update(){
	std::default_random_engine generator;
	std::uniform_real_distribution<float> distribution(this->min_velocity, this->max_velocity);
	std::uniform_int_distribution<int> direction(-1, 1); //Acepto velocidad 0

	this->velocity = distribution(generator);
	this->velocity *= direction(generator);
}