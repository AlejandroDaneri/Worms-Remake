#ifndef __SOCKETEXCEPTION_H__
#define __SOCKETEXCEPTION_H__

#include <exception>
#include <string>

class SocketException: public std::exception{
	private:
		std::string msg;

	public:
		//Crea la excepcion
		explicit SocketException(std::string msg);

		//Destruye la excepcion
		virtual ~SocketException();

		//Devuelve el mensaje de error
		virtual const char* what() const noexcept;
};

#endif
