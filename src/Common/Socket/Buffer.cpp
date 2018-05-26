#include "Buffer.h"

#define MAX_BUF_LEN 200

Buffer::Buffer(): buffer(new char[MAX_BUF_LEN]), offset(0){}

Buffer::~Buffer(){
	if (this->buffer){
		delete[] buffer;
	}
}

Buffer::Buffer(const Buffer& other): buffer(new char[MAX_BUF_LEN]){
	for (size_t i = 0; i < other.offset; i++){
		this->buffer[i] = other.buffer[i];
	}
	this->offset = other.offset;
}

Buffer::Buffer(Buffer&& other): buffer(other.buffer), offset(other.offset){
	other.buffer = NULL;
}
