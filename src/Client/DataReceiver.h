#ifndef __DATARECEIVER_H__
#define __DATARECEIVER_H__

#include "Thread.h"
#include "ViewsList.h"


class DataReceiver: public Thread{
	private:
		ViewsList& views;
		//Socket socket/////////////////////////////////////////////////////////////// o protocolo esta clase es despues la que va a recibir datos del socket

	public:
		DataReceiver(ViewsList& views);
		~DataReceiver();

		void run() override;


		ViewsList& getViewsList(){
			return this->views;///////////////////////////////////////////////////Este metodo lo hago solo para probar, cuando haya sockets se va
		}

};


#endif
