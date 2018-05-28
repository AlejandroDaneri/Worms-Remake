#ifndef __BUFFER_H__
#define __BUFFER_H__

#include <cstddef>

/* Clase que representa un buffer de almacenamiento de datos */
class Buffer{
	private:
		char* buffer;
		size_t offset;

	public:
		/* Constructor */
		Buffer();

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
