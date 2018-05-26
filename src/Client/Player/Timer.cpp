#include "Timer.h"
#include "Handlers.h"

const int TIME_STEP = 50;
const int MINIMUM_TIME = 750;

Timer::Timer(Handlers& handlers, int time) : 
	actual_time(0), max_time(time), handlers(handlers) {}

Timer::~Timer() {}

bool Timer::startCallBack() {
	this->actual_time += TIME_STEP;

	if (this->actual_time == this->max_time + MINIMUM_TIME) {
        // Hace explotar el arma
        this->handlers.timerStopped(this->actual_time);
    }
	return this->actual_time < this->max_time + MINIMUM_TIME;
}

void Timer::start() {
    this->actual_time = MINIMUM_TIME;
    this->my_connection = Glib::signal_timeout().connect(sigc::mem_fun(*this, &Timer::startCallBack), TIME_STEP);
}

void Timer::stop() {
    if (this->my_connection.connected()) {
        this->my_connection.disconnect();
        this->handlers.timerStopped(this->actual_time);
    }
}
