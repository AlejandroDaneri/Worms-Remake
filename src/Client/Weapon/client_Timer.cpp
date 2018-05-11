#include "client_Timer.h"
#include "client_Player.h"

#define TIMER 60

Timer::Timer(int time) : running(true), max_time(time) {}

Timer::~Timer() {}

void Timer::run() { // recibe el arma
	int actual_time = 0;
	while (this->running && actual_time < this->max_time) {
		sleep(1);
		actual_time++;
	}
	// Hace explotar el arma
	this->running = false;
}

void Timer::stopRun() {
	this->running = false;
}

