#include "WeaponPowerAccum.h"
#include "Handlers.h"

const int TIME_STEP = 50;
const int MINIMUM_POWER = 1000;
const int POWER_STEP = 15;

WeaponPowerAccum::WeaponPowerAccum(Handlers& handlers, int time) : 
	actual_time(0), max_time(time), handlers(handlers) {}

WeaponPowerAccum::~WeaponPowerAccum() {}

bool WeaponPowerAccum::startCallBack() {
	this->actual_time += TIME_STEP;
	this->power += POWER_STEP;

	if (this->actual_time == this->max_time) {
		this->handlers.powerAccumStopped(this->power);
		return false;
	}
	return true;
}

void WeaponPowerAccum::start() {
	this->actual_time = 0;
	this->power = MINIMUM_POWER;
	this->my_connection = Glib::signal_timeout().connect(sigc::mem_fun(*this, &WeaponPowerAccum::startCallBack), TIME_STEP);
}

void WeaponPowerAccum::stop() {
	if (this->my_connection.connected()) {
		this->my_connection.disconnect();
		this->handlers.powerAccumStopped(this->power);
	}
}
