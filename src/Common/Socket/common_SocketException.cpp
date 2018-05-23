#include "SocketException.h"
#include <string>
#include <errno.h>
#include <cstring>

SocketException::SocketException(std::string msg): msg(msg){
	this->msg += " : ";
	this->msg += strerror(errno);
	this->msg.insert(0, "Error en el socket: ");
}

SocketException::~SocketException(){}

const char* SocketException::what() const noexcept{
	return this->msg.c_str();
}
