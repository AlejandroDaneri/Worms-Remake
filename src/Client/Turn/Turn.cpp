#include "Turn.h"
#include <glibmm/main.h>
#include "Player.h"

const int TIME_DEFAULT = 60;
const int REDUCTION_TIME_DEFAULT = 3;
const int LIMIT_TIME = 10;

Turn::Turn(Player& player, TurnLabel& time_label):
	actual_time(TIME_DEFAULT), player(player), time_label(time_label),
	max_time(TIME_DEFAULT), reduction_time(REDUCTION_TIME_DEFAULT){}

Turn::~Turn() {}

bool Turn::startCallBack() {
	if (this->actual_time <= LIMIT_TIME){
		this->player.playTickTime();
	}

	this->actual_time--;
	if (this->actual_time < 0){
		return false;
	}
	this->time_label.setTime(this->actual_time);
	return true;
}

void Turn::start() {
	this->actual_time = this->max_time;
	this->my_connection = Glib::signal_timeout().connect(sigc::mem_fun(*this, &Turn::startCallBack), 1000);
}

void Turn::reduceTime() {
	this->actual_time = this->reduction_time;
}

void Turn::stop() {
	if (this->my_connection.connected()) {
		this->my_connection.disconnect();
	}
}

void Turn::setTime(int time, int reduction_time){
	this->max_time = time;
	this->reduction_time = reduction_time;
}
