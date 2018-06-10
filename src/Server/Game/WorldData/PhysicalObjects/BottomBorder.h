#ifndef __BOTTOMBORDER_H__
#define __BOTTOMBORDER_H__

#include "PhysicalObject.h"
#include <string>

//Determina el borde inferior del mundo
class BottomBorder: public PhysicalObject{
	private:
		std::string type;

	protected:
		void getBodyDef(b2BodyDef& body_def, const b2Vec2& pos) override;
		void createFixtures() override;

	public:
		explicit BottomBorder(World& world);
		~BottomBorder();
};

#endif
