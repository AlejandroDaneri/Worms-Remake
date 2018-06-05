#ifndef __WEAPON_H__
#define __WEAPON_H__

#include "PhysicalObject.h"
#include "GameParameters.h"
#include "World.h"
#include "WeaponExplodeTime.h"
#include <string>
#include "WeaponNames.h"
#include "RayCastWeaponExploded.h"

class Worm;

class Weapon: public PhysicalObject{
	protected:
		GameParameters& parameters;
		int damage;
		int radius;
		bool waiting_to_explode;
		int time_to_explode;
		float angle;
		float power;
		int shooter_id;
		WeaponExplodeTime explode_time;
		RayCastWeaponExploded explosion;

		virtual void createFixtures() override;
		virtual void setInitialVelocity() override;

		//Ataca a los gusanos en el radio de explosion
		void attackWormExplosion(const b2Vec2& center, int angle);

	public:
		static int weapon_id;

		Weapon(World& world, GameParameters& parameters, int damage, int radius = 0);
		virtual ~Weapon();

		//Devuelve true si el arma esta en movimiento o esperando para explotar
		bool isActive() override;

		//Carga los datos para disparar el arma
		virtual void shoot(char dir, int angle, int power, int time, int shooter_id);

		//Dispara un arma teledirigida
		virtual void shoot(Worm& shooter, b2Vec2 pos);

		//Explota el arma
		virtual void explode();

		virtual void collideWithSomething(CollisionData *other) override;

		void getBodyDef(b2BodyDef& body_def, const b2Vec2& pos) override;

		virtual const std::string& getName() = 0;

		int getShooterId() const;

};

#endif
