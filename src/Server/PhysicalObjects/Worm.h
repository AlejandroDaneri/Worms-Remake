#ifndef __WORM_H__
#define __WORM_H__

#include "PhysicalObject.h"
#include "GameParameters.h"
#include "Weapon.h"

class Worm: public PhysicalObject{	
	private:
		int player_id;
		int life;
		char dir;
		GameParameters& parameters;
		physical_object_ptr weapon;
		float max_height;
		int colliding_with_girder;
		int friction;
		int angle;

	protected:
		void getBodyDef(b2BodyDef& body_def, const b2Vec2& pos) override;
		void createFixtures() override;

	public:
		Worm(World& world, GameParameters& parameters, int id, int player_id);
		~Worm();

		int getPlayerId() const;
		int getLife() const;
		char getDir() const;
		bool isColliding() const;
		const std::string& getCurrentWeapon() const;

		//Aumenta la vida del gusano
		void addLife(int life);

		//Reduce la vida del gusano
		void reduce_life(int damage);

		//Ejecuta una accion de movimiento del gusano
		void move(char action);

		//Cambia el arma del gusano
		void changeWeapon(const std::string& weapon);

		//Dispara un arma no teledirigida
		void shoot(int angle, int power, int time);

		//Dispara un arma teledirigida
		void shoot(b2Vec2 pos);

		//Analiza la colision con el objeto
		void collide_with_something(CollisionData* other) override;

		//Analiza el fin del contacto con una viga
		void end_collission_girder(char friction);

		//Recibe danio de un arma o una explosion
		void receive_weapon_damage(int damage, const b2Vec2& epicenter);

		//Devuelve true si el gusano esta en movimiento
		bool isActive() override;
};

#endif
