#ifndef __CLIENTWEAPON_H__
#define __CLIENTWEAPON_H__

#include <string>

class Weapon {
	protected:
		std::string name;
		int ammo;
		bool has_Scope;
		bool is_Timed;
		bool is_Fragmentable;

	public:
		Weapon(std::string name, int ammo);
		~Weapon() {}
		
		virtual bool hasScope();
		virtual bool isSelfDirected();
		virtual bool isFragmentable();
		virtual bool isTimed();
		virtual bool hasVariablePower();
		virtual void changeTime(int time) = 0;
		virtual int getTime();
		virtual std::string getName();
};
#endif