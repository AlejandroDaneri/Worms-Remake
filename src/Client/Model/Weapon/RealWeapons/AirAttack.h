#ifndef __CLIENTAIRATTACK_H__
#define __CLIENTAIRATTACK_H__

#include "SelfDirectedWeapon.h"

/* Clase que representa al arma AirStrike */
class AirAttack : public SelfDirectedWeapon {
public:
	/* Constructor */
	explicit AirAttack(int ammo);

	/* Destructor */
	~AirAttack();

	/* Constructor por movimiento */
	AirAttack(AirAttack&& other);
};

#endif
