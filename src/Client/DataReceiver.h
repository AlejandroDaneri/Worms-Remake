#ifndef __DATARECEIVER_H__
#define __DATARECEIVER_H__

#include "Thread.h"
#include "client_Player.h"
#include "ViewsList.h"
#include "client_Protocol.h"


class DataReceiver: public Thread{
	private:
		ViewsList& views;
		Player& player;
		Protocol& protocol;

	public:
		DataReceiver(ViewsList& views, Player& player, Protocol& protocol);
		~DataReceiver();

		void run() override;

};


#endif
