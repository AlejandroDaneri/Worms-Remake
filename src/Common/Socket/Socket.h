#ifndef __SOCKET_H__
#define __SOCKET_H__

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include "SocketException.h"

class Socket{
	private:
		int fd;

		/* Constructor privado del socket */
		explicit Socket(int fd);

		/* Clase privada para encapsular getaddrinfo y hacerlo RAII */
		class Addrinfo;

	public:
		/* Clase que encapsula los parametros que se deben recibir del servidor */
		class Server;

		/* Clase que encapsula los parametros que se deben recibir del cliente */
		class Client;

		/* Constructor del socket para el cliente
		 * Crea el socket y lo conecta
		 * Lanza SocketException si ocurre un error */
		explicit Socket(Socket::Client client);

		/* Constructor del socket para el servidor
		 * Crea el socket y lo asocia al puerto inidicado
		 * Lanza SocketException si ocurre un error */
		explicit Socket(Socket::Server server);

		/* Envia todos los datos del buffer data a traves del socket
		 * Devuelve la cantidad de datos que se pudieron enviar
		 * Lanza SocketException en caso de error */
		int sendData(const void *data, size_t size);

		/* Recibe datos del socket hasta alcanzar el max
		 * o hasta que se cierra la conexion
		 * Devuelve la cantidad de datos que se pudieron recibir
		 * Lanza SocketException en caso de error */
		int receive(void* buffer, size_t size);

		/* Establece una conexion con un cliente */
		Socket acceptClient();

		/* Interrumpe las conexiones del socket */
		void stop();

		/* Cierra y destruye el socket */
		~Socket();

		/* Constructor y pasaje por movimiento */
		Socket(Socket&& other);
		Socket& operator=(Socket&& other);

		/* Bloqueo la copia */
		Socket(Socket& other) = delete;
		bool operator=(Socket& other) = delete;
};

class Socket::Addrinfo{
	private:
		struct addrinfo* addrinfo;

	public:
		/* Constructor */
		Addrinfo(const char* host, const char* service, int flag);

		/* Crea el socket y lo conecta o bindea segun correponda
		 * Devuelve el socket creado
		 * y lanza una excepcion si no pudo crearse */
		Socket connectOrBind(int action) const;

		/* Destructor */
		~Addrinfo();
};

class Socket::Server{
	private:
		const char* service;
		int max_client_wait;

	public:
        /* Constructor */
		Server(const char* service, int max_client_wait);

		/* Destructor */
		~Server();

		/* Devuelve el servicio */
		const char* getService() const;

		/* Devuelve la cantidad maxima de clientes en espera */
		int getMaxClientWait() const;
};

class Socket::Client{
	private:
		const char* host;
		const char* service;

	public:
        /* Constructor */
		Client(const char* host, const char* service);

        /* Destructor */
		~Client();

        /* Devuelve el Host */
		const char* getHost() const;

		/* Devuelve el servicio */
		const char* getService() const;
};

#endif
