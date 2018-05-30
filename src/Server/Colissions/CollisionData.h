#ifndef __COLLISIONDATA_H__
#define __COLLISIONDATA_H__

#include <string>


class PhysicalObject;

//Datos de un objeto para determinar colisiones
class CollisionData{
	private:
		std::string type;
		PhysicalObject* object;

	public:
		CollisionData(std::string type, PhysicalObject* object);
		~CollisionData();

		const std::string& getType();
		PhysicalObject* getObject();
};

#endif
