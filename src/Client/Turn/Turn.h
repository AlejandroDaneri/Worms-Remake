#ifndef __CLIENTTURN_H__
#define __CLIENTTURN_H__

#include "TurnLabel.h"

class Player;

class Turn {
	private:
		int actual_time;
		Player& player;
		TurnLabel& time_label;
		sigc::connection my_connection;

		bool startCallBack();

	public:
		Turn(Player& player, TurnLabel& time_label);
		~Turn();

	    void start();
		void reduceTime();
		void stop();
};

#endif
