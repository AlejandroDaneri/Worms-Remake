#ifndef __BOTTOMBORDER_H__
#define __BOTTOMBORDER_H__

#include "PhysicalObject.h"

class BottomBorder: public PhysicalObject{
	private:


	protected:
		void getBodyDef(b2BodyDef& body_def, const b2Vec2& pos) override;
		void createFixtures() override;

	public:
		BottomBorder(World& world);
		~BottomBorder();

		//virtual void collide_with_something(CollisionData other) = 0;

};

#endif
