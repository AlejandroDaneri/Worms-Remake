#ifndef __CLIENTEXPLOSIONVIEWLIST_H__
#define __CLIENTEXPLOSIONVIEWLIST_H__

#include <vector>
#include "client_explosionView.h"

class ExplosionViewList {
	private:
		std::vector<std::unique_ptr<ExplosionView>> list;

	public:
		ExplosionViewList();
		~ExplosionViewList();
		
		void push_back(std::unique_ptr<ExplosionView>&& animation);
		
		void check();
		
		int size();
};


#endif
