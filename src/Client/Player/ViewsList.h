#ifndef __VIEWSLIST_H__
#define __VIEWSLIST_H__

#include <unordered_map>
#include <vector>
#include <string>
#include "WorldView.h"
#include "WormView.h"
#include "BulletView.h"
#include "GirderView.h"
#include "PlayersList.h"
#include "ExplosionView.h"
#include "ExplosionViewList.h"
#include "MusicPlayer.h"

/* Clase que se encarga de almacenar los objetos visibles */
class ViewsList{
	private:
		WorldView& world;
		Player& player;
		PlayersList& players_list;
		std::unordered_map<int, WormView> worms;
		std::unordered_map<int, BulletView> weapons;
		std::vector<GirderView> girders;
		Gtk::Image scope;
		int current_worm_id;
		int weapon_focused;
        ExplosionViewList animation;
        MusicPlayer& musicPlayer;

        /* Elimina el focus sobre el worm */
        void removeWormFocus();

        /* CallBacks */
        bool removeWormCallBack(int id);
        bool removeWeaponCallBack(int id);
        bool updateWormDataCallBack(int id, int player_id, float pos_x, float pos_y, int life, char dir, bool colliding);
        bool updateWeaponDataCallBack(int id, const std::string& weapon_name, float pos_x, float pos_y);
        bool updateScopeCallBack(int angle);
        bool removeScopeVisibilityCallBack();
        bool addGirderCallBack(size_t size, int pos_x, int pos_y, int rotation);
        bool setCurrentWormCallBack(int id);
        bool setVictoryCallBack();

	public:
        /* Constructor */
		ViewsList(WorldView& world, Player& player, PlayersList& players_list, MusicPlayer& musicPlayer);

		/* Destructor */
		~ViewsList();

        /* Elimina al worm de la vista actualizando la vida del player */
		void removeWorm(int id);

        /* Elimina la vista del arma y la reemplaza por la animacion de la explosion */
		void removeWeapon(int id);

		/* Actualiza la posicion y la vida del worm */
        void updateWormData(int id, int player_id, float pos_x, float pos_y, int life, char dir, bool colliding);

		/* Actualiza la posicion del arma */
        void updateWeaponData(int id, const std::string& weapon_name, float pos_x, float pos_y);

        /* CallBack de changeWeapon */
        bool changeWeaponCallBack(const std::string &weapon_name);

		/* Actualiza la vista del worm con el arma nueva */
        void changeWeapon(const std::string &weapon_name);

        /* Actualiza la posicion del scope */
		void updateScope(int angle);

		/* Esconde la vista del scope */
        void removeScopeVisibility();

        /* Agrega una viga a la vista en la posicion indicada y
         * con la rotacion indicada */
		void addGirder(size_t size, int pos_x, int pos_y, int rotation);

		/* Actualiza el worm actual y hace focus en este */
        void setCurrentWorm(int id);

        void setVictory();
};


#endif
