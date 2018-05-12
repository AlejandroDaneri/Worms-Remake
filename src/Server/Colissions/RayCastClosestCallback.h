#ifndef __RAYCASTCLOSESTCALLBACK_H__
#define __RAYCASTCLOSESTCALLBACK_H__

#include "b2Body.h"
#include "b2Fixture.h"
#include "b2WorldCallbacks.h"

class RayCastClosestCallback: public b2RayCastCallback{
	private:
		b2Body* closest;
		b2Vec2 normal;

	public:
		RayCastClosestCallback();
		~RayCastClosestCallback();

		b2Body* getClosestBody();
		b2Vec2 getClosestNormal();

		float32 ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float32 fraction) override;
};


#endif
