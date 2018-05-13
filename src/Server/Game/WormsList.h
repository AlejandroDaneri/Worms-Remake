#ifndef __WORMSLIST_H__
#define __WORMSLIST_H__

#include "Worm.h"
#include <vector>

class WormsList{
	private:
		std::vector<physical_object_ptr> list;
		size_t current;

	public:
		WormsList();

		~WormsList();

		Worm& getCurrentWorm();

		void begin_turn();

		void add(physical_object_ptr worm);

		WormsList(WormsList&& other);

		void distribute(size_t max, int life_to_add);

		bool isEmpty();

};

#endif
