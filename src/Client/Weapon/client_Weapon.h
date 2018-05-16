#ifndef __CLIENTWEAPON_H__
#define __CLIENTWEAPON_H__

#include <string>

class Weapon {
	protected:
		std::string name;
		unsigned int ammo;
		bool has_Scope;
		bool is_Timed;
		bool is_Fragmentable;

	public:
		Weapon(std::string name, int ammo);
		~Weapon();
		Weapon(Weapon&& other);
		Weapon& operator=(Weapon&& other);
		
		virtual bool hasScope();
		virtual bool isSelfDirected();
		virtual bool isFragmentable();
		virtual bool isTimed();
		virtual bool hasVariablePower();
		virtual std::string getName();
		virtual void shoot();
		virtual bool hasAmmo();
};
#endif
