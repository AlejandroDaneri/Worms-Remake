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

		//Devuelve el tipo del objeto fisico
		const std::string& getType();

		//Devuelve el objeto fisico
		PhysicalObject* getObject();
};

#endif
