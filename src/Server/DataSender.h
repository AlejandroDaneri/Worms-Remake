#ifndef __DATASENDER_H__
#define __DATASENDER_H__

#include "Thread.h"
#include "World.h"
#include "PhysicalObject.h"
#include <list>


#include "ViewsList.h"////////////////////////////////////////////////////////////

class DataSender: public Thread{
	private:
		std::list<physical_object_ptr>& objects;
		//Socket socket/////////////////////////////////////////////////////////////// o protocolo esta clase es despues la que va a enviar datos pos socket
		ViewsList& views;/////////////////////////////////////////////////

	public:
		DataSender(World& world, ViewsList& views);//////////////////////////////Eliminar ViewsList& views
		~DataSender();

		void run() override;

};


#endif
