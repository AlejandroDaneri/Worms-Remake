#ifndef __WEAPONEXPLODETIME_H__
#define __WEAPONEXPLODETIME_H__

#include "Thread.h"
#include <mutex>

class Weapon;
class World;

class WeaponExplodeTime: public Thread{
	private:
		Weapon& weapon;
		World& world;
		int time;

	public:
		WeaponExplodeTime(World& world, Weapon& weapon);
		~WeaponExplodeTime();

		void setTime(int time);

		void run() override;

};

#endif
