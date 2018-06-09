#ifndef WORMS_EXPLOSIONVIEWLIST_H
#define WORMS_EXPLOSIONVIEWLIST_H

#include <list>
#include "ExplosionView.h"

/* Clase que se encarga de almacenar animaciones de explosiones */
class ExplosionViewList {
	private:
		std::list<ExplosionView> animations;

		/* Verifica si alguna animacion de la lista finalizo y las
		 * elimina de la lista */
		void check();

	public:
		/* Constructor */
		ExplosionViewList();

		/* Destructor */
		~ExplosionViewList();


		/* Agrega una animacion de explosion a la lista y la reproduce */
		void addAndStart(ExplosionView&& animation);

};


#endif //WORMS_EXPLOSIONVIEWLIST_H
