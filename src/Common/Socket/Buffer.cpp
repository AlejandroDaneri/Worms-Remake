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

void Buffer::setNext(char value){
	this->buffer[this->offset++] = value;
}

char Buffer::getNext(){
	return this->buffer[this->offset++];
}

char* Buffer::getPointer(){
	return this->buffer;
}

void Buffer::incrementOffset(size_t value){
	this->offset += value;
}

size_t Buffer::getSize() const{
	return this->offset;
}
