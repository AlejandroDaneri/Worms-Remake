#include "client_Timer.h"
#include "client_Player.h"

Timer::Timer(Player& player, int32_t time) : actual_time(0), max_time(time),
														player(player) {}

Timer::~Timer() {}

void Timer::run() { // recibe el arma
	while (this->running && this->actual_time < this->max_time) {
		sleep(1);
		this->actual_time++;
	}
	// Hace explotar el arma
	player.shoot(this->actual_time);
	this->running = false;
}

int32_t Timer::getTime() {
	return this->actual_time;
}

