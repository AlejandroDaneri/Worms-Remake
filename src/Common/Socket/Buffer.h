#ifndef __BUFFER_H__
#define __BUFFER_H__

#include <cstddef>

class Buffer{
	public:
		char* buffer;
		size_t offset;

		Buffer();

		~Buffer();

		Buffer(const Buffer& other);

		Buffer& operator=(const Buffer& other) = delete;

		Buffer(Buffer&& other);
};

#endif
