#include "client_Timer.h"
#include "client_Player.h"

const int TIME_STEP = 50;
const int MINIMUM_TIME = 750;

Timer::Timer(Player& player, int32_t time) : actual_time(0), max_time(time),
														player(player) {}

Timer::~Timer() {}

void Timer::run() {
	while (this->running && this->actual_time < this->max_time) {
		std::this_thread::sleep_for(std::chrono::milliseconds(TIME_STEP));
		this->actual_time += TIME_STEP;
	}
	// Hace explotar el arma
	player.shoot(this->actual_time + MINIMUM_TIME);
	this->running = false;
}

