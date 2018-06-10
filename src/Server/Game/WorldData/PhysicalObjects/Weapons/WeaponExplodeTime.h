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

		//Setea el tiempo de explosion
		void setTime(int time);

		//Cuenta el tiempo que falta para que el arma explote
		void run() override;

};

#endif
