#ifndef __RAYCASTWEAPONEXPLODED_H__
#define __RAYCASTWEAPONEXPLODED_H__

#include "b2Body.h"
#include "b2Fixture.h"
#include "b2WorldCallbacks.h"
#include <vector>

class RayCastWeaponExploded: public b2RayCastCallback{
	private:
		std::vector<b2Body*> affected_worms;
		b2Body* closest;

	public:
		RayCastWeaponExploded();
		~RayCastWeaponExploded();

		b2Body* getClosestWorm();

		float32 ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float32 fraction) override;
};


#endif
