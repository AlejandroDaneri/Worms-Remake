#ifndef __BUFFER_H__
#define __BUFFER_H__

#include <cstddef>

#define MAX_BUF_LEN 200

/* Clase que representa un buffer de almacenamiento de datos */
class Buffer{
	private:
		char* buffer;
		size_t offset;
		size_t max_size;

	public:
		/* Constructor */
		Buffer(size_t max_size = MAX_BUF_LEN);

		/* Destructor */
		~Buffer();

		/* Constructor por copia */
		Buffer(const Buffer& other);

		/* Operador = por copia */
		Buffer& operator=(const Buffer& other) = delete;

		/* Constructor por movimiento */
		Buffer(Buffer&& other);

		/* Agrega el valor al buffer */
		void setNext(char value);

		/* Devuelve el siguiente elemento del buffer */
		char getNext();

		/* Devuelve un puntero al buffer */
		char* getPointer();

		/* Incrementa el valor del offset */
		void incrementOffset(size_t value);

		/* Devuelve el tamaño del buffer */
		size_t getSize() const;
};

#endif
