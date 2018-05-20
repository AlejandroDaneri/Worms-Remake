#ifndef __CLIENTWEAPON_H__
#define __CLIENTWEAPON_H__

#include <string>

class Weapon {
	protected:
		std::string name;
		unsigned int ammo;
		bool has_Scope;
		bool is_Timed;

	public:
		Weapon(std::string name, int ammo);
		~Weapon();
		Weapon(Weapon&& other);
		Weapon& operator=(Weapon&& other);
		
		virtual bool hasScope() const;
		virtual bool isSelfDirected() const;
		virtual bool isTimed() const;
		virtual bool hasVariablePower() const;
		virtual const std::string& getName() const;
		virtual void shoot();
		virtual bool hasAmmo() const;

		unsigned int getAmmo() const;
};
#endif
