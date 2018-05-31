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
		void addEffect(const std::string& audio);

	public:
		/* Constructor */
		MusicPlayer();

		/* Destructor */
		~MusicPlayer();

		/* Reproduce la musica de fondo */
		void playMusic();

		/* Reproduce el sonido de inicio de turno */
		void playStartTurnSound();

		/* Reproduce el sonido de falta de tiempo */
		void playTickSound();

		/* Reproduce el sonido de muerte de un worm */
		void playDeathSound();

		/* Reproduce el sonido de daño recibido */
		void playDamageReceiveSound();

		/* Reproduce el sonido de la explosion */
		void playExplosionSound(const std::string& weapon);

		/* Reproduce el sonido de arma disparada */
		void playWeaponShotSound(const std::string& weapon);

		/* Reproduce el sonido de salto o rollback */
		void playJumpSound(char action);

		/* Reproduce el sonido de arma seleccionada */
		void playSelectWeaponSound();

		/* Reproduce el sonido de victoria */
		void playVictory();

		/* Reproduce el sonido de arma descargada */
		void playNoAmmo();

		/* Detiene la reproduccion de la musica de fondo */
		void stop();
};


#endif
