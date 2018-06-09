#ifndef __WORMSLIST_H__
#define __WORMSLIST_H__

#include <vector>
#include "Worm.h"

class WormsList{
	private:
		std::vector<physical_object_ptr> list;
		size_t current;

	public:
        /* Constructor */
		WormsList();

		/* Destructor */
		~WormsList();

		/* Devuelve el worm actual */
		Worm& getCurrentWorm();

		/* Comienza el turno, cambiando el gusano actual */
		void beginTurn();

		/* Agrega un worm a la lista */
		void add(physical_object_ptr worm);

		/* Constructor por movimiento */
		WormsList(WormsList&& other);

		/* Aumenta la vida de los worms si la cantidad de
		 * worms es menor que la de otros jugadores */
		void distribute(size_t max, int life_to_add);

		/* Devuelve true si todos los worms estan muertos */
		bool isEmpty();

		/* Mata a todos los worms */
		void kill();
};

#endif
