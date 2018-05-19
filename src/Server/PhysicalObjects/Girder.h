#ifndef __GIRDER_H__
#define __GIRDER_H__

#include "PhysicalObject.h"
#include "GameParameters.h"

class Girder: public PhysicalObject{
	private:
		size_t size;
		int rotation;
		int max_rotation_to_friction;

	protected:
		void getBodyDef(b2BodyDef& body_def, const b2Vec2& pos) override;
		void createFixtures() override;

	public:
		Girder(World& world, GameParameters& parameters, size_t size, int rotation);
		~Girder();

		size_t getSize();
		int getRotation();

		bool has_friction();

};

#endif
