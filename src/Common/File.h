#ifndef __FILE_H__
#define __FILE_H__

#include <fstream>
#include <string>
#include <ios>

#define FILE_READ_MODE std::fstream::in
#define FILE_WRITE_MODE std::fstream::out | std::fstream::trunc

typedef std::ios_base::openmode file_mode;


class File{
	private:
		std::fstream file;

	public:
		//Crea el archivo, sino se puede lanza excepcion
		File(std::string name, file_mode mode);

		//Destruye el archivo
		~File();

		//Escribe el buffer en el archivo
		void write_buffer(const char* buffer, size_t size);

		//Lee parte del archivo y lo guarda en el buffer
		void read_buffer(char* buffer, size_t size);

		//Devuelve la siguiente linea del archivo
		std::string get_line();

		//Devuelve el tamanio del archivo
		//Post: no se modifica nada del archivo
		size_t size();

		//Devuelve la cantidad de caracteres leidos en la ultima operacion
		size_t gcount() const;

		//Devuelve true si se alcanzo EOF, false si no
		bool eof() const;

		//Constructor por movimiento
		File(File&& other);

		//Pasaje por copia
		File(const File& other) = delete;
		File& operator=(const File& other) = delete;

		//Escribe en el archivo el objeto
		template <class T>
		File& operator<<(const T& object){
			this->file << object;
			return *this;
		}
};

#endif
