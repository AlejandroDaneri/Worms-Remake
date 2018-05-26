#include "Protocol.h"
#include <cstring>

Protocol::Protocol(Socket&& socket) : socket(std::move(socket)){}

Protocol::Protocol(Protocol&& other) : socket(std::move(other.socket)) {}

Protocol::~Protocol() {}

void Protocol::send_buffer(Buffer& buffer) {
	uint32_t len_converted = htonl(buffer.offset);
	std::lock_guard<std::mutex> lock(this->mutex_send);
	this->socket.send_data(&len_converted, sizeof len_converted);
	this->socket.send_data(buffer.buffer, buffer.offset);
}

Buffer Protocol::receive_buffer() {
	uint32_t len;
	this->socket.receive(&len, sizeof (uint32_t));
	len = ntohl(len);

	Buffer buffer;
	this->socket.receive(buffer.buffer, len);
	return std::move(buffer);
}

void Protocol::send_int_buffer(Buffer& buffer, int32_t value) {
	value = htonl(value);
	std::memcpy(buffer.buffer + buffer.offset, &value, sizeof(value));
	buffer.offset += sizeof(value);
}

int Protocol::receive_int_buffer(Buffer& buffer) {
	int32_t value;
	std::memcpy(&value, buffer.buffer + buffer.offset, sizeof(value));
	buffer.offset += sizeof(value);
	return ntohl(value);
}

void Protocol::send_string_buffer(Buffer& buffer, const std::string &string) {
	for (size_t j = 0; j < string.size(); j++){
		buffer.buffer[buffer.offset++] = string[j];
	}
	buffer.buffer[buffer.offset++] = '\0';
}

std::string Protocol::receive_string_buffer(Buffer& buffer) {
	std::string string;
	while (buffer.buffer[buffer.offset] != '\0'){
		string += buffer.buffer[buffer.offset++];
	}
	buffer.offset++;
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
