#include "MusicPlayer.h"
#include "MusicPlayerException.h"
#include "WeaponNames.h"
#include "Path.h"

const std::string BACKGROUND_MUSIC = SOUNDS_PATH + "BackgroundMusic.mp3";
const std::string START_TURN_SOUND = SOUNDS_PATH + "Misc/StartRound.wav";
const std::string TICK_SOUND = SOUNDS_PATH + "Misc/TimerTick.wav";
const std::string RUN_AWAY_SOUND = SOUNDS_PATH + "Worms/RunAway.wav";
const std::string DEATH_SOUND = SOUNDS_PATH + "Worms/Death.wav";
const std::string EXPLOSION_SOUND = SOUNDS_PATH + "Weapons/Explosion.wav";
const std::string TELEPORT_SOUND = SOUNDS_PATH + "Weapons/Teleportation.wav";
const std::string BAT_SOUND = SOUNDS_PATH + "Weapons/BaseballSound.wav";
const std::string HOLY_GRENADE_SOUND = SOUNDS_PATH + "Weapons/HolyGrenade.wav";
const std::string AIR_ATTACK_SOUND = SOUNDS_PATH + "Weapons/AirAttack.wav";
const std::string SHOOT_SOUND  = SOUNDS_PATH + "Weapons/ShootWeapon.wav";
const std::string ROLLBACK_SOUND = SOUNDS_PATH + "Misc/RollBack.wav";
const std::string JUMP_SOUND = SOUNDS_PATH + "Misc/Jump.wav";
const std::string SELECT_WEAPON_SOUND = SOUNDS_PATH + "Misc/SelectWeapon.wav";
const std::string NO_AMMO_SOUND = SOUNDS_PATH + "Misc/NoAmmo.wav";
const std::string VICTORY_SOUND = SOUNDS_PATH + "Worms/Victory.WAV";

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

void MusicPlayer::playWeaponShotSound(const std::string& weapon){
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

void MusicPlayer::playJumpSound(int dir) {
	if (dir == -1) {
		this->addEffect(ROLLBACK_SOUND);
	} else {
		this->addEffect(JUMP_SOUND);
	}
}

void MusicPlayer::playSelectWeaponSound() {
	this->addEffect(SELECT_WEAPON_SOUND);
}
