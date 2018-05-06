#ifndef __WORM_H__
#define __WORM_H__

#include "PhysicalObject.h"

class Worm: public PhysicalObject{	
	protected:
		void getBodyDef(b2BodyDef& body_def, const b2Vec2& pos) override;
		void createFixtures() override;

	public:
		Worm(World& world, int id);
		~Worm();

		//virtual void collide_with_something(CollisionData other) = 0;

};

#endif
