#ifndef __BUFFER_H__
#define __BUFFER_H__

#include <cstddef>

class Buffer{
	private:
		char* buffer;
		size_t offset;

	public:

		Buffer();

		~Buffer();

		void setNext(char value);

		char getNext();

		char* getPointer();

		void incrementOffset(size_t value);

		size_t getSize() const;

		Buffer(const Buffer& other);

		Buffer& operator=(const Buffer& other) = delete;

		Buffer(Buffer&& other);
};

#endif
