#include "client_Turn.h"
#include "client_Player.h"

#define TIMER 60000
#define REDUCTION_TIME 3000
#define TIME_STEP 50

Turn::Turn(Player& player) : actual_time(0), max_time(TIMER), player(player) {}

Turn::~Turn() {}

void Turn::run() {
	while (this->running && this->actual_time < this->max_time) {
		std::this_thread::sleep_for(std::chrono::milliseconds(TIME_STEP));
		this->actual_time += TIME_STEP;
	}
	player.endTurn();
	this->running = false;
}

void Turn::reduceTime() {
	this->max_time = this->actual_time + REDUCTION_TIME;
}
