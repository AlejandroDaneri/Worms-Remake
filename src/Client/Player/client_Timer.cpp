#include "client_Timer.h"
#include "Handlers.h"

const int TIME_STEP = 50;
const int MINIMUM_TIME = 750;

Timer::Timer(Handlers& handlers, int time) : 
	actual_time(0), max_time(time), handlers(handlers) {}

Timer::~Timer() {}

void Timer::run() {
	while (this->running && this->actual_time < this->max_time) {
		std::this_thread::sleep_for(std::chrono::milliseconds(TIME_STEP));
		this->actual_time += TIME_STEP;
	}
	// Hace explotar el arma
	handlers.timerStopped(this->actual_time + MINIMUM_TIME);
	this->running = false;
}

