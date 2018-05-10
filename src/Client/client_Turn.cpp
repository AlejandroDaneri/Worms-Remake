#include "client_Turn.h"
#include "client_Player.h"

#define TIMER 60

Turn::Turn(Player& player) : running(true),
	actual_time(0), max_time(TIMER), player(player) {}

Turn::~Turn() {}

void Turn::run() {
	this->actual_time = 0;
	while (this->running && this->actual_time < this->max_time) {
		sleep(1);
		this->actual_time++;
	}
	player.endTurn();
	this->running = false;
}

void Turn::stopRun() {
	this->running = false;
}

void Turn::reduceTime(int timeReduction) {
	this->max_time = this->actual_time + timeReduction;
}
