#include "SocketException.h"
#include <string>

SocketException::SocketException(std::string msg): msg(msg){
	this->msg.insert(0, "Error en el socket: ");
}

SocketException::~SocketException(){}

const char* SocketException::what() const noexcept{
	return this->msg.c_str();
}
