#ifndef __CLIENTMELEEWEAPON_H__
#define __CLIENTMELEEWEAPON_H__

#include "client_Weapon.h"

class MeleeWeapon : public Weapon {
	private:
		int time;
	public:
		MeleeWeapon(std::string name, int ammo, bool scope, int time = -1);
		~MeleeWeapon() {}
		
		void changeTime(int time) override;
		int getTime() override;
};

#endif
