#include "Turn.h"
#include <glibmm/main.h>
#include "Player.h"

const int TIMER = 60;
const int REDUCTION_TIME = 3;
const int LIMIT_TIME = 10;

Turn::Turn(Player& player, TurnLabel& time_label):
	actual_time(TIMER), player(player), time_label(time_label){}

Turn::~Turn() {}

bool Turn::startCallBack() {
    this->time_label.setTime(this->actual_time);
    if (this->actual_time <= LIMIT_TIME){
        this->player.play_tick_time();
    }
    if (this->actual_time == 0) { //////////////////// Cambiarlo a que el protocolo llame a endTurn
        this->player.endTurn();
    }
    this->actual_time--;
    return this->actual_time >= 0;
    /* while (this->running && this->actual_time < this->max_time) {
		this->time_label.setTime((this->max_time - this->actual_time) / 1000);
		for (int i = 0; i < ITERATIONS_ONE_SECOND && this->running && this->actual_time <= this->max_time; i++) {
			std::this_thread::sleep_for(std::chrono::milliseconds(TIME_STEP));
			this->actual_time += TIME_STEP;
		}
		if (this->actual_time > this->max_time - LIMIT_TIME){
			this->player.play_tick_time();
		}
	}
	
	this->player.endTurn();
	this->running = false; */
}

void Turn::start() {
    this->actual_time = TIMER;
    this->my_connection = Glib::signal_timeout().connect(sigc::mem_fun(*this, &Turn::startCallBack), 1000);
}

void Turn::reduceTime() {
	this->actual_time = REDUCTION_TIME;
}

void Turn::stop() {
    this->my_connection.disconnect();
}
