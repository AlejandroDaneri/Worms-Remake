#ifndef __MUSICPLAYER_H__
#define __MUSICPLAYER_H__

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <map>
#include <string>

class MusicPlayer {
	private:
		Mix_Music* music; // Musica de fondo
        std::map<int, Mix_Chunk*> effects;

        void check(int channel);
        void addEffect(std::string audio);

	public:
		MusicPlayer();
		~MusicPlayer();
		
		void playMusic();

		//////////// Ver de cambiar a un unico metodo y que se le pase el path
		//void playEffect(std::string audio);
		void playTickSound();
        void playWalkSound();
        void playExplosionSound();
        void playTeleportSound();
        void playHolyGrenadeSound();

		void stop();
		bool isPlaying();
};


#endif
