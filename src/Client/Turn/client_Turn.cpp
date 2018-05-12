#include "client_Turn.h"
#include "client_Player.h"

#define TIMER 60
#define REDUCTION_TIME 3

Turn::Turn(Player& player) : actual_time(0), max_time(TIMER), player(player) {}

Turn::~Turn() {}

void Turn::run() {
	while (this->running && this->actual_time < this->max_time) {
		sleep(1);
		this->actual_time++;
	}
	player.endTurn();
	this->running = false;
}

void Turn::reduceTime() {
	this->max_time = this->actual_time + REDUCTION_TIME;
}
