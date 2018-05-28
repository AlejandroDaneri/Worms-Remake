#ifndef __SELFDIRECTEDWEAPON_H__
#define __SELFDIRECTEDWEAPON_H__

#include "Weapon.h"

/* Clase que representa las armas teledirigidas */
class SelfDirectedWeapon: public Weapon{
	public:
	    /* Constructor */
		SelfDirectedWeapon(std::string name, int ammo);

		/* Destructor */
		~SelfDirectedWeapon();

		/* Constructor por movimiento */
		SelfDirectedWeapon(SelfDirectedWeapon&& other);

		/* Devuelve true si es teledirigida */
		bool isSelfDirected() const override;
};

#endif
