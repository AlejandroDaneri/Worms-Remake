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
        this->player.playTickTime();
    }
    if (this->actual_time == 0) {
        this->player.endTurn();
    }
    this->actual_time--;
    return this->actual_time >= 0;
}

void Turn::start() {
    this->actual_time = TIMER;
    this->my_connection = Glib::signal_timeout().connect(sigc::mem_fun(*this, &Turn::startCallBack), 1000);
}

void Turn::reduceTime() {
	this->actual_time = REDUCTION_TIME;
}

void Turn::stop() {
    if (this->my_connection.connected()) {
        this->my_connection.disconnect();
        this->player.endTurn();
    }
}
