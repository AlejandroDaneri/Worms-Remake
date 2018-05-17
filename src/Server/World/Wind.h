#ifndef __WIND_H__
#define __WIND_H__

#include "GameParameters.h"

class Wind{
	private:
		float min_velocity;
		float max_velocity;
		float velocity;

	public:
		Wind(GameParameters& parameters);
		~Wind();

		float getVelocity() const;
		void update();

};


#endif
