#ifndef __MUSICPLAYER_H__
#define __MUSICPLAYER_H__

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

class MusicPlayer {
	private:
		Mix_Chunk* effects = NULL; // efectos especiales
		Mix_Music* music = NULL; // Musica de fondo

	public:
		MusicPlayer();
		~MusicPlayer();
		
		void playMusic();
		void playTickSound();
		void stop();
};


#endif
