#include "client_Turn.h"
#include "client_Player.h"

const int TIMER = 60000;
const int REDUCTION_TIME = 3000;
const int TIME_STEP = 50;
const int LIMIT_TIME = 10000;

Turn::Turn(Player& player, TurnLabel& time_label):
	actual_time(0), max_time(TIMER), player(player), time_label(time_label){}

Turn::~Turn() {}

void Turn::run() {
	while (this->running && this->actual_time < this->max_time - LIMIT_TIME) {
		for (int i = 0; i < 20 && this->running && this->actual_time <= this->max_time; i++) {
			std::this_thread::sleep_for(std::chrono::milliseconds(TIME_STEP));
			this->actual_time += TIME_STEP;
		}
		this->time_label.setTime((this->max_time - this->actual_time) / 1000);
	}
	// Inicio la cuenta regresiva
	while (this->running && this->actual_time < this->max_time) {
		this->player.play_tick_time();
		for (int i = 0; i < 20 && this->running && this->actual_time <= this->max_time; i++) {
			std::this_thread::sleep_for(std::chrono::milliseconds(TIME_STEP));
			this->actual_time += TIME_STEP;
		}
		this->time_label.setTime((this->max_time - this->actual_time) / 1000);
	}
	this->player.endTurn();
	this->running = false;
}

void Turn::reduceTime() {
	this->max_time = this->actual_time + REDUCTION_TIME;
}
