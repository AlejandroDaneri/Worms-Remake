#ifndef __WIND_H__
#define __WIND_H__

#include "GameParameters.h"

class Wind{
	private:
		float min_velocity;
		float max_velocity;
		float velocity;

	public:
		explicit Wind(GameParameters& parameters);
		~Wind();

		//Devuelve la velocidad del viento
		float getVelocity() const;

		//Actualiza la velocidad del viento
		void update();
};


#endif
