#ifndef __CLIENTTURN_H__
#define __CLIENTTURN_H__

#include "Thread.h"
#include <unistd.h>
#include "TurnLabel.h"

class Player;

class Turn : public Thread {
	private:
		int actual_time;
		int max_time;
		Player& player;
		TurnLabel& time_label;

	public:
		Turn(Player& player, TurnLabel& time_label);
		~Turn();

		void run();
		void reduceTime();
};

#endif
