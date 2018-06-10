#include "MusicPlayerException.h"
#include <string>

MusicPlayerException::MusicPlayerException(std::string msg) : msg(msg) {
	this->msg.insert(0, "Error en Music Player: ");
}

MusicPlayerException::~MusicPlayerException() {}

const char* MusicPlayerException::what() const noexcept {
	return this->msg.c_str();
}
