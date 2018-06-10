#include "MusicPlayer.h"
#include <map>
#include <string>
#include "MusicPlayerException.h"
#include "WeaponNames.h"
#include "Protocol.h"
#include "MusicPath.h"

MusicPlayer::MusicPlayer() {
	this->music = NULL;
	// Initialize SDL.
	if (SDL_Init(SDL_INIT_AUDIO) < 0) {
		throw MusicPlayerException("Error al inicializar SDL");
	}

	//Initialize SDL_mixer
	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1) {
		throw MusicPlayerException("Error al inicializar SDL mixer");
	}

	// Load background music
	this->music = Mix_LoadMUS(BACKGROUND_MUSIC.c_str());
	if (this->music == NULL) {
	}
}

MusicPlayer::~MusicPlayer() {
	Mix_HaltChannel(-1);
	this->stop();
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

void MusicPlayer::addEffect(const std::string& audio) {
	int channel;
	Mix_Chunk* effect = NULL;
	effect = Mix_LoadWAV(audio.c_str());
	if (effect == NULL) {
		return;
	}
	if ((channel = Mix_PlayChannel(-1, effect, 0)) == -1) {
		Mix_FreeChunk(effect);
		return;
	}
	this->check(channel);
	this->effects.insert(std::make_pair(channel, effect));
}

void MusicPlayer::playMusic() {
	Mix_PlayMusic(this->music, -1);
	Mix_VolumeMusic(MIX_MAX_VOLUME / 4);
}

void MusicPlayer::playStartTurnSound() {
	this->addEffect(START_TURN_SOUND);
}

void MusicPlayer::playTickSound() {
	this->addEffect(TICK_SOUND);
}

void MusicPlayer::playDeathSound() {
	this->addEffect(DEATH_SOUND);
}

void MusicPlayer::playDamageReceiveSound() {
	this->addEffect(DAMAGE_RECEIVE_SOUND);
}

void MusicPlayer::playExplosionSound(const std::string& weapon) {
	if (weapon == HOLY_GRENADE_NAME) {
		this->addEffect(HOLY_GRENADE_SOUND);
	} else {
		this->addEffect(EXPLOSION_SOUND);
	}
}

void MusicPlayer::playVictory() {
	this->addEffect(VICTORY_SOUND);
}

void MusicPlayer::playNoAmmo() {
	this->addEffect(NO_AMMO_SOUND);
}

void MusicPlayer::stop() {
	Mix_HaltMusic();
}

void MusicPlayer::playWeaponShotSound(const std::string& weapon) {
	if (weapon == TELEPORT_NAME) {
		this->addEffect(TELEPORT_SOUND);
	} else if (weapon == BAT_NAME) {
		this->addEffect(BAT_SOUND);
	} else if (weapon == DYNAMITE_NAME) {
		this->addEffect(RUN_AWAY_SOUND);
	} else if (weapon == AIR_ATTACK_NAME) {
		this->addEffect(AIR_ATTACK_SOUND);
	} else {
		this->addEffect(SHOOT_SOUND);
	}
}

void MusicPlayer::playJumpSound(char action) {
	if (action == ROLLBACK) {
		this->addEffect(ROLLBACK_SOUND);
	} else if (action == JUMP) {
		this->addEffect(JUMP_SOUND);
	}
}

void MusicPlayer::playSelectWeaponSound() {
	this->addEffect(SELECT_WEAPON_SOUND);
}
