#ifndef __PROTOCOL_H__
#define __PROTOCOL_H__

#include <string>
#include "Buffer.h"
#include "Socket.h"
#include "File.h"

#define MAX_STRING_SIZE 200

#define CREATE_GAME_ACTION 0
#define JOIN_GAME_ACTION 1
#define START_GAME_ACTION 2

#define MOVING_OBJECT 0
#define DEAD_OBJECT 1
#define ACTION 2


#define START_TURN 3
#define END_TURN 4
#define MOVE_ACTION 5
#define CHANGE_WEAPON_ACTION 6
#define SHOOT_WEAPON_ACTION 7
#define SHOOT_WEAPON 8
#define SHOOT_SELF_DIRECTED 9
#define MOVE_SCOPE 10

#define END_GAME 11

#define NO_SEND_DATA 100


#define MOVE_RIGHT 1
#define MOVE_LEFT -1
#define JUMP 2
#define ROLLBACK 3

#define WORM_TYPE 0
#define WEAPON_TYPE 1
#define GIRDER_TYPE 2

/* Clase que se encarga de enviar y recibir mensajes por socket
 * utilizando un formato determinado */
class Protocol {
	private:
		Socket socket;
	public:
		/* Constructor */
		Protocol(Socket&& socket);

		/* Constructor por copia */
		Protocol(Protocol&& other);

		/* Destructor */
		~Protocol();

		/* Envia el contenido del buffer */
		virtual void sendBuffer(Buffer &buffer);

		/* Recibe un mensaje, lo almacena en un buffer y lo retorna */
		Buffer receiveBuffer();


		/* Agrega el valor al buffer cumpliendo las caracteristicas del protocolo */
		static void sendIntBuffer(Buffer &buffer, int32_t value);

		/* Retorna el valor del entero recibido almacenado en el buffer */
		static int receiveIntBuffer(Buffer &buffer);


		/* Almacena el string en el buffer  */
		static void sendStringBuffer(Buffer &buffer, const std::string &string);

		/* Retorna el string recibido que se encuentra almacenado en el buffer */
		static std::string receiveStringBuffer(Buffer &buffer);


		/* Envia la longitud */
		void sendLength(uint32_t length);

		/* Envia la longitud */
		static Buffer sendLengthBuffer(uint32_t length);

		/* Recibe la longitud y la retorna */
		size_t receiveLength();

		/* Cierra la comunicacion */
		void stop();

		/* Envia un char */
		void sendChar(unsigned char c);

		/* Recibe un char */
		unsigned char receiveChar();

		/* Envia un string */
		void sendString(const std::string &string);

		/* Recibe un string */
		std::string receiveString();

		/* Envia el archivo,
		Post: el archivo no se modifica */
		static Buffer sendFile(File& file);

		/* Recibe una imagen */
		std::string receiveImage();
};

#endif
