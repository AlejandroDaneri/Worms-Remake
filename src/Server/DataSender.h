#ifndef __DATASENDER_H__
#define __DATASENDER_H__

#include "Thread.h"
#include "World.h"
#include "PhysicalObject.h"
#include "server_Protocol.h"
#include <list>

class DataSender: public Thread{
	private:
		std::list<physical_object_ptr>& objects;
		Protocol& protocol;

	public:
		DataSender(World& world, Protocol& protocol);
		~DataSender();

		void run() override;

		void stop() override;

};


#endif
