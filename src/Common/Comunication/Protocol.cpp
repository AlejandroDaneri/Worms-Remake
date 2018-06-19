#include "Protocol.h"
#include <cstring>
#include <string>

Protocol::Protocol(Socket&& socket) : socket(std::move(socket)){}

Protocol::Protocol(Protocol&& other) : socket(std::move(other.socket)) {}

Protocol::~Protocol() {}

void Protocol::sendBuffer(Buffer &buffer) {
	uint32_t len_converted = htonl(buffer.getSize());
	this->socket.sendData(&len_converted, sizeof len_converted);
	this->socket.sendData(buffer.getPointer(), buffer.getSize());
}

Buffer Protocol::receiveBuffer() {
	uint32_t len;
	this->socket.receive(&len, sizeof(uint32_t));
	len = ntohl(len);

	Buffer buffer(len);
	this->socket.receive(buffer.getPointer(), len);
	return std::move(buffer);
}

void Protocol::sendIntBuffer(Buffer &buffer, int32_t value) {
	value = htonl(value);
	std::memcpy(buffer.getPointer() + buffer.getSize(), &value, sizeof(value));
	buffer.incrementOffset(sizeof(value));
}

int Protocol::receiveIntBuffer(Buffer &buffer) {
	int32_t value;
	std::memcpy(&value, buffer.getPointer() + buffer.getSize(), sizeof(value));
	buffer.incrementOffset(sizeof(value));
	return ntohl(value);
}

void Protocol::sendStringBuffer(Buffer &buffer, const std::string &string) {
	for (size_t j = 0; j < string.size(); j++){
		buffer.setNext(string[j]);
	}
	buffer.setNext('\0');
}

std::string Protocol::receiveStringBuffer(Buffer &buffer) {
	std::string string;
	char c;
	while ((c = buffer.getNext()) != '\0'){
		string += c;
	}
	return string;
}

void Protocol::sendLength(uint32_t length){
	uint32_t converted = htonl(length);
	this->socket.sendData(&converted, sizeof(uint32_t));
}

Buffer Protocol::sendLengthBuffer(uint32_t length){
	Buffer buffer;
	Protocol::sendIntBuffer(buffer, length);
	return buffer;
}

size_t Protocol::receiveLength(){
	int32_t length;
	this->socket.receive(&length, sizeof(int32_t));
	return ntohl(length);
}

void Protocol::stop(){
	this->socket.stop();
}

void Protocol::sendString(const std::string &string){
	size_t string_length = string.size();
	this->sendLength(string_length);
	this->socket.sendData(string.c_str(), string_length);
}

std::string Protocol::receiveString(){
	uint32_t length = this->receiveLength();
	char buffer [MAX_STRING_SIZE + 1];
	this->socket.receive(buffer, length);
	buffer[length] = '\0';
	return std::move(std::string(buffer));
}

void Protocol::sendChar(unsigned char c){
	this->socket.sendData(&c, sizeof(unsigned char));
}

unsigned char Protocol::receiveChar(){
	unsigned char c;
	this->socket.receive(&c, sizeof(unsigned char));
	return c;
}

