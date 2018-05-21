#include "MusicPlayerException.h"
#include <string>
#include <errno.h>
#include <cstring>

MusicPlayerException::MusicPlayerException(std::string msg): msg(msg){
	this->msg += " : ";
	this->msg += strerror(errno);
	this->msg.insert(0, "Error en el socket: ");
}

MusicPlayerException::~MusicPlayerException(){}

const char* MusicPlayerException::what() const noexcept{
	return this->msg.c_str();
}
