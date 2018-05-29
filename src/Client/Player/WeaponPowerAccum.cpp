#include "WeaponPowerAccum.h"
#include "Handlers.h"

const int TIME_STEP = 50;
const int MINIMUM_TIME = 750;

WeaponPowerAccum::WeaponPowerAccum(Handlers& handlers, int time) : 
	actual_time(0), max_time(time), handlers(handlers) {}

WeaponPowerAccum::~WeaponPowerAccum() {}

bool WeaponPowerAccum::startCallBack() {
	this->actual_time += TIME_STEP;

	if (this->actual_time == this->max_time + MINIMUM_TIME) {
        // Hace explotar el arma
        this->handlers.timerStopped(this->actual_time);
    }
	return this->actual_time < this->max_time + MINIMUM_TIME;
}

void WeaponPowerAccum::start() {
    this->actual_time = MINIMUM_TIME;
    this->my_connection = Glib::signal_timeout().connect(sigc::mem_fun(*this, &WeaponPowerAccum::startCallBack), TIME_STEP);
}

void WeaponPowerAccum::stop() {
    if (this->my_connection.connected()) {
        this->my_connection.disconnect();
        this->handlers.timerStopped(this->actual_time);
    }
}
