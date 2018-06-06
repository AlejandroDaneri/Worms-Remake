#include "Buffer.h"


Buffer::Buffer(size_t max_size): buffer(new char[max_size]),
	offset(0), max_size(max_size){}

Buffer::~Buffer(){
	if (this->buffer){
		delete[] buffer;
	}
}

Buffer::Buffer(const Buffer& other): buffer(new char[other.max_size]){
	for (size_t i = 0; i < other.max_size; i++){
		this->buffer[i] = other.buffer[i];
	}
	this->offset = other.offset;
	this->max_size = other.max_size;
}

Buffer::Buffer(Buffer&& other): buffer(other.buffer),
	offset(other.offset), max_size(other.max_size){
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

size_t Buffer::getMaxSize() const{
	return this->max_size;
}
