#ifndef __WORMSLIST_H__
#define __WORMSLIST_H__

#include "Worm.h"
#include <vector>

class WormsList{
	private:
		std::vector<Worm> list;
		size_t current;

	public:
		WormsList(std::vector<Worm>&& worms);

		~WormsList();

		Worm& getCurrentWorm();

		void changeWorm();

		WormsList(WormsList&& other);

};

#endif
