#ifndef __GIRDER_H__
#define __GIRDER_H__

#include "PhysicalObject.h"

class Girder: public PhysicalObject{
	private:
		size_t size;
	protected:
		void getBodyDef(b2BodyDef& body_def, const b2Vec2& pos) override;
		void createFixtures() override;

	public:
		Girder(World& world, size_t size);
		~Girder();

};

#endif
