#ifndef __MUSICPLAYER_H__
#define __MUSICPLAYER_H__

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <map>
#include <string>

/* Clase que se enecarga de reproducir musica y efectos
 * de sonido */
class MusicPlayer {
	private:
		Mix_Music* music; // Musica de fondo
        std::map<int, Mix_Chunk*> effects;

        void check(int channel);
        void addEffect(std::string audio);

	public:
		/* Constructor */
		MusicPlayer();

		/* Destructor */
		~MusicPlayer();

		/* Reproduce la musica de fondo */
		void playMusic();

		//////////// Ver de cambiar a un unico metodo y que se le pase el path
		//void playEffect(std::string audio);

		/* Reproduce el sonido de inicio de turno */
		void playStartTurnSound();

		/* Reproduce el sonido de falta de tiempo */
		void playTickSound();

		/* Reproduce el sonido del worm caminando */
        void playWalkSound();

        /* Reproduce el sonido de boring del worm */
        void playBoring();

        /* Reproduce el sonido de run away del worm */
        void playRunAway();

        /* Reproduce el sonido de muerte de un worm */
        void playDeathSound();

        /* Reproduce el sonido de la explosion */
        void playExplosionSound();

        /* Reproduce el sonido de la teletransportacion */
        void playTeleportSound();

		/* Reproduce el sonido del bate */
		void playBatSound();

        /* Reproduce el sonido de la granada santa */
        void playHolyGrenadeSound();

        /* Reproduce el sonido de arma descargada */
		void playNoAmmo();

        /* Detiene la reproduccion de la musica de fondo */
		void stop();

		/* Devuelve true si la musica de fondo se esta reproduciendo */
		bool isPlaying();
};


#endif
