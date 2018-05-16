#include "client_Timer.h"
#include "client_Player.h"

#define TIME_STEP 50

Timer::Timer(Player& player, int32_t time) : actual_time(0), max_time(time),
														player(player) {}

Timer::~Timer() {}

void Timer::run() { // recibe el arma
	while (this->running && this->actual_time < this->max_time) {
		std::this_thread::sleep_for(std::chrono::milliseconds(TIME_STEP));
		this->actual_time += TIME_STEP;
	}
	// Hace explotar el arma
	if (!this->running)
		printf("Shoot por el stop\n");
	else {
		printf("Shoot por cargar al maximo\n");
	}
	player.shoot(this->actual_time);
	this->running = false;
}

