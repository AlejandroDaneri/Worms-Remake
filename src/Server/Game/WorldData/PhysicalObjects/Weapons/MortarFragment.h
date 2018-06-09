#ifndef __SERVERMORTARFRAGMENT_H__
#define __SERVERMORTARFRAGMENT_H__

#include "Fragment.h"

class MortarFragment: public Fragment{
	public:

		MortarFragment(World& world, GameParameters& parameters);
		~MortarFragment();

		const std::string& getName() override;

		bool isWindAffected() override;

};

#endif
