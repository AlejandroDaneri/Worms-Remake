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

		//Devuelve la longitud de la viga
		size_t getSize();

		//Devuelve la rotacion de la viga
		int getRotation();

		//Devuelve true si la viga tiene friccion
		bool hasFriction();

		//Devuelve la rotacion normalizada
		int getAngle();

};

#endif
