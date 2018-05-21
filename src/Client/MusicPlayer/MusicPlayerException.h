#ifndef __MUSICPLAYEREXCEPTION_H__
#define __MUSICPLAYEREXCEPTION_H__

#include <exception>
#include <string>

class MusicPlayerException: public std::exception{
	private:
		std::string msg;

	public:
		//Crea la excepcion
		explicit MusicPlayerException(std::string msg);

		//Destruye la excepcion
		virtual ~MusicPlayerException();

		//Devuelve el mensaje de error
		virtual const char* what() const noexcept;
};

#endif
