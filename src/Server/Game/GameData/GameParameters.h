#ifndef __GAMEPARAMETERS_H__
#define __GAMEPARAMETERS_H__

#include <string>
#include <vector>
#include <map>
#include "b2Math.h"
#include "yaml.h"
#include "File.h"

// Clase que lee los archivos de configuracion 
// y devuelve los parametros obtenidos
class GameParameters{
	public:
		class GirderParams;

	private:
		std::map<std::string, float> float_parameters;
		std::map<std::string, int> weapon_radius;
		std::map<std::string, unsigned int> weapon_ammo;
		std::map<std::string, int> weapon_damage;
		std::map<std::string, int> weapon_fragments;

		std::vector<b2Vec2> worms;
		std::vector<GirderParams> girders;
		File background_image;

	public:
		//Inicializa todos los parametros necesarios para la partida
		GameParameters(const std::string& config_file, const std::string& config_editor_file);
		~GameParameters();

		//Devuelve la vida del worm
		int getWormLife();

		//Devuelve la vida a agregar de los worms
		int getWormsLifeToAdd();


		//Devuelve los worms del mapa
		std::vector<b2Vec2>& getWorms();

		//Devuelve la vigas del mapa
		std::vector<GirderParams>& getGirders();

		//Devuelve la municion de las armas
		std::map<std::string, unsigned int>& getWeaponsAmmo();


		//Devuelve la velocidad del worm
		float getWormVelocity();

		//Devuelve la velocidad del worm debido a una explosion
		float getWormExplosionVelocity();

		//Devuelve la velocidad de salto del worm
		float getWormJumpVelocity();

		//Devuelve la velocidad del rollback del worm
		float getWormRollbackVelocity();

		//Devuelve la altura de salto del worm
		float getWormJumpHeight();

		//Devuelve la altura del rollback del worm
		float getWormRollbackHeight();


		//Devuelve la altura en la cual el worm sufre daño
		int getWormHeightToDamage();

		//Devuelve el daño maximo por caida
		int getWormMaxHeightDamage();


		//Devuelve la velocidad del arma
		float getWeaponsVelocity();


		//Devuelve el daño del arma
		int getWeaponDamage(const std::string& weapon);

		//Devuelve el radio de daño del arma
		int getWeaponRadius(const std::string& weapon);

		//Devuelve la cantidad de fragmentos del arma
		int getWeaponFragments(const std::string& weapon);


		//Devuelve la velocidad minima del viento
		float getWindMinVelocity();

		//Devuelve la velocidad maxima del viento
		float getWindMaxVelocity();

		//Devuelve la gravedad
		float getGravity();

		//Devuelve la separacion de los misiles aereos
		float getAirMissilesSeparation();


		//Devuelve la rotacion maxima para la cual
		//el gusano no desliza
		int getMaxGirderRotationToFriction();

		//Establece la altura maxima
		void setMaxHeight(int height);

		//Devuelve la altura maxima
		int getMaxHeight();


		//Devuelve el tiempo de sleep del DataSender
		int getDataSenderSleep();

		//Devuelve el tiempo de sleep del World
		int getGameWaitingWorldSleep();

		//Devuelve el tiempo de sleep del step del World
		int getWorldSleepAfterStep();

		//Devuelve el time step del World
		float getWorldTimeStep();


		//Devuelve el tiempo del turno
		int getTurnTime();

		//Devuelve el tiempo adicional luego de un disparo
		int getTimeAfterShoot();


		//Devuelve la imagen de fondo
		File& getBackgroundImage();
};

class GameParameters::GirderParams{
	public:
		size_t len;
		float pos_x;
		float pos_y;
		int rotation;

		GirderParams(size_t len, float pos_x, float pos_y, int rotation);
};

typedef GameParameters::GirderParams GirderParams;

#endif
