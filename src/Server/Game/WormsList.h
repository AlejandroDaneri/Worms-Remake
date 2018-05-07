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

		worm_ptr getCurrentWorm();

		void begin_turn();

		void add(physical_object_ptr worm);

		WormsList(WormsList&& other);

};

#endif
