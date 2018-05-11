#ifndef __SELFDIRECTEDWEAPON_H__
#define __SELFDIRECTEDWEAPON_H__

#include "Weapon.h"

class SelfDirectedWeapon: public Weapon{
	private:
		int quantity;

	protected:
		Position getEpicenter(const Position& origin, const dir_ptr& dir, int angle, int power);

	public:
		SelfDirectedWeapon(int munitions, int radius, int damage, int quantity);
		~SelfDirectedWeapon();

		void shoot(const Position& pos);

		bool hasScope();
		bool hasVariablePower();
		bool isTimed();
		bool isSelfDirected();

};

#endif