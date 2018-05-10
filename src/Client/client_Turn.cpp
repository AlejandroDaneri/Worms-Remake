#include "client_Turn.h"

Turno::Turno(int max_time, Player& player) : running(true),
	actual_time(0), max_time(max_time), player(player) {}

Turno::~Turno() {}

void Turno::run() {
	while (this->running && this->actual_time < this->max_time) {
		sleep(1);
		this->actual_time++;
	}
	this->player.endTurn();
	this->running = false;
}

void Turno::stopRun() {
	this->running = false;
}

void Turno::reduceTime(int timeReduction) {
	this->max_time = this->actual_time + timeReduction;
}
