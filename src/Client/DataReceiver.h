#ifndef __DATARECEIVER_H__
#define __DATARECEIVER_H__

#include "Thread.h"
#include "ViewsList.h"
#include "ClientProtocol.h"

class Player;

class DataReceiver: public Thread{
	private:
		ViewsList& views;
		Player& player;
		ClientProtocol& protocol;

	public:
		DataReceiver(ViewsList& views, Player& player, ClientProtocol& protocol);
		~DataReceiver();

		void run() override;

		void stop() override;

};


#endif
