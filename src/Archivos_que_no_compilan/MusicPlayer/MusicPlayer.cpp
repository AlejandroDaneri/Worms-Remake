#include "MusicPlayer.h"
#include <iostream>
#include "MusicPlayerException.h"

const std::string BACKGROUND_MUSIC = "resources/Sounds/menu principal/music.mp3"; ///////////////// cambiar
const std::string TICK_SOUND = "resources/Sounds/misc/TIMERTICK.WAV";
const std::string WALK_SOUND = "resources/Sounds/misc/Walk-Expand.wav";
const std::string EXPLOSION_SOUND = "resources/Sounds/Weapons/Explosion1.wav";
const std::string TELEPORT_SOUND = "resources/Sounds/Weapons/TELEPORT.WAV";
const std::string HOLY_GRENADE_SOUND = "resources/Sounds/Weapons/HOLYGRENADE.WAV";

MusicPlayer::MusicPlayer() {
    this->music = NULL;
    // Initialize SDL.
    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        throw MusicPlayerException("Error al inicializar SDL");
    }

    //Initialize SDL_mixer
    if (Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1) {
        throw MusicPlayerException("Error al inicializar SDL mixer");
    }

    // Load background music
    this->music = Mix_LoadMUS(BACKGROUND_MUSIC.c_str());
    if (this->music == NULL) {
        std::cout << "Error al cargar el audio" << std::endl;
    }
}

MusicPlayer::~MusicPlayer() {
    Mix_HaltChannel(-1);
    if (this->music != NULL) {
        Mix_FreeMusic(this->music);
    }
    std::map<int, Mix_Chunk*>::iterator iter;
    for (iter = this->effects.begin(); iter != this->effects.end(); iter++) {
        Mix_FreeChunk(iter->second);
    }
    // quit SDL_mixer
    Mix_CloseAudio();
    Mix_Quit();
    SDL_Quit();
}

void MusicPlayer::check(int channel) {
    if (this->effects.find(channel) != this->effects.end()) {
        // elimino el audio anterior de este canal
        Mix_FreeChunk(this->effects.at(channel));
        this->effects.erase(channel);
    }
    std::map<int, Mix_Chunk*>::iterator iter = this->effects.begin();
    while (iter != this->effects.end()) {
        if (!Mix_Playing(iter->first)) {
            Mix_FreeChunk(iter->second);
            iter = this->effects.erase(iter);
        } else {
            iter++;
        }
    }
}

void MusicPlayer::addEffect(std::string audio) {
    int channel;
    Mix_Chunk* effect = NULL;
    effect = Mix_LoadWAV(audio.c_str());
    if (effect == NULL) {
        std::cout << "Error al cargar el audio" << std::endl;
        return;
    }
    if ((channel = Mix_PlayChannel(-1, effect, 0)) == -1) {
        std::cout << "Error al reproducir el audio" << std::endl;
        Mix_FreeChunk(effect);
        return;
    }
    this->check(channel);
    this->effects.insert(std::make_pair(channel, effect));
}

void MusicPlayer::playMusic() {
	if (Mix_PlayMusic(this->music, -1) == -1) {
        std::cout << "Error al reproducir el audio" << std::endl;
    }
}

/*void playEffect(std::string audio) {
    this->addEffect(audio);
}*/

void MusicPlayer::playTickSound() {
    this->addEffect(TICK_SOUND);
}

void MusicPlayer::playWalkSound() {
    this->addEffect(WALK_SOUND);
}

void MusicPlayer::playExplosionSound() {
    this->addEffect(EXPLOSION_SOUND);
}

void MusicPlayer::playTeleportSound() {
    this->addEffect(TELEPORT_SOUND);
}

void MusicPlayer::playHolyGrenadeSound() {
    this->addEffect(HOLY_GRENADE_SOUND);
}

void MusicPlayer::stop() {
    Mix_HaltMusic();
}

bool MusicPlayer::isPlaying() {
    return Mix_PlayingMusic();
}
