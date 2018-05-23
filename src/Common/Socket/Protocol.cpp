#include "Protocol.h"
#include <cstring>

Protocol::Protocol(Socket&& socket) : socket(std::move(socket)){}

Protocol::Protocol(Protocol&& other) : socket(std::move(other.socket)) {}

Protocol::~Protocol() {}

void Protocol::send_buffer(const char* buffer, size_t size) {
	uint32_t len_converted = htonl(size);
	std::lock_guard<std::mutex> lock(this->mutex_send);
	this->socket.send_data(&len_converted, sizeof len_converted);
	this->socket.send_data(buffer, size);
}

size_t Protocol::receive_buffer(char* buffer) {
	uint32_t len;
	this->socket.receive(&len, sizeof (uint32_t));
	len = ntohl(len);

	this->socket.receive(buffer, len);
	return len;
}

void Protocol::send_int(char* buffer, size_t& offset, int32_t value) {
	value = htonl(value);
	std::memcpy(buffer + offset, &value, sizeof(value));
	offset += sizeof(value);
}

int Protocol::receive_int(char* buffer, size_t& offset) {
	int32_t value;
	std::memcpy(&value, buffer + offset, sizeof(value));
	offset += sizeof(value);
	return ntohl(value);
}

void Protocol::send_string(char* buffer, size_t& offset, const std::string& string) {
	for (size_t j = 0; j < string.size(); offset++, j++){
		buffer[offset] = string[j];
	}
	buffer[offset++] = '\0';
}

std::string Protocol::receive_string(char* buffer, size_t& offset) {
	std::string string;
	while (buffer[offset] != '\0'){
		string += buffer[offset++];
	}
	offset++;
	return string;
}

void Protocol::send_length(uint32_t length){
	uint32_t converted = htonl(length);
	this->socket.send_data(&converted, sizeof(uint32_t));
}

size_t Protocol::receive_length(){
	int32_t length;
	this->socket.receive(&length, sizeof(int32_t));
	return ntohl(length);
}

void Protocol::stop(){
	this->socket.stop();
}
