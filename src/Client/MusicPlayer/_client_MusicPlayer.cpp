#include "client_MusicPlayer.h"
#include <string>
#include "MusicPlayerException.h"

const std::string BACKGROUND_MUSIC = "resources/Sounds/menu principal/music.mp3"; ///////////////// cambiar
const std::string TICK_SOUND = "resources/Sounds/misc/TIMERTICK.WAV";

MusicPlayer::MusicPlayer() {
	this->effects = NULL;
	// Initialize SDL.
	if (SDL_Init(SDL_INIT_AUDIO) < 0)
		throw MusicPlayerException("Error al inicializar SDL");
			
	//Initialize SDL_mixer 
	if( Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 ) == -1 ) 
		throw MusicPlayerException("Error al inicializar SDL mixer");
		
	// Load background music
	this->music = Mix_LoadMUS(MUS_PATH);
	if (this->music == NULL)
		throw MusicPlayerException("Error al cargar el audio");
}

MusicPlayer::~MusicPlayer() {
	if (this->effects != NULL)
		Mix_FreeChunk(this->effects);
	if (this->music != NULL)
		Mix_FreeMusic(this->music);
	
	// quit SDL_mixer
	Mix_CloseAudio();
}

void MusicPlayer::playMusic() {
	if (Mix_PlayMusic(this->music, -1) == -1)
		throw MusicPlayerException("Error al reproducir el audio");
}

void MusicPlayer::playTickSound() {
	if (this->wave != NULL)
		Mix_FreeChunk(this->effects);
	this->effects = Mix_LoadWAV(TICK_SOUND);
	if (this->effects == NULL)
		throw MusicPlayerException("Error al cargar el audio");
	if (Mix_PlayChannel(-1, this->effects, 0) == -1)
		throw MusicPlayerException("Error al reproducir el audio");
}

