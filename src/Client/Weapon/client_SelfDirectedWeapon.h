#ifndef __SELFDIRECTEDWEAPON_H__
#define __SELFDIRECTEDWEAPON_H__

#include "client_Weapon.h"

class SelfDirectedWeapon: public Weapon{
	private:
		int quantity;

	protected:
		//Position getEpicenter(const Position& origin, const dir_ptr& dir, int angle, int power);

	public:
		SelfDirectedWeapon(std::string name, int ammo, int quantity);
		~SelfDirectedWeapon();

		//void shoot(const Position& pos);

		bool isSelfDirected() override;
		void changeTime(int time) override;
};

#endif
