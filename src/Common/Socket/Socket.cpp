#include <stdexcept>
#include <cstring>
#include "Socket.h"

#define SERVER 0
#define CLIENT 1

Socket::Socket(Socket::Client client) : fd(-1) {
	Addrinfo addrinfo(client.getHost(), client.getService(), 0);
	*this = addrinfo.connectOrBind(CLIENT);
}

Socket::Socket(Socket::Server server) : fd(-1) {
	char* host = NULL; //ANY
	int flag = AI_PASSIVE;
	Addrinfo addrinfo(host, server.getService(), flag);
	Socket sckt = addrinfo.connectOrBind(SERVER);

	if ((listen(sckt.fd, server.getMaxClientWait())) == -1){
		throw SocketException("Error en listen");
	}

	*this = std::move(sckt);
}

Socket::Socket(int fd): fd(fd){}

Socket::~Socket(){
	this->stop();
}

Socket::Socket(Socket&& other): fd(other.fd){
	other.fd = -1;
}

Socket& Socket::operator=(Socket&& other){
	if (this != &other) {
		this->fd = other.fd;
		other.fd = -1;
	}
	return *this;
}

int Socket::sendData(const void *data, size_t size){
	size_t total_send = 0;
	int actual_send;

	while (total_send < size){
		int len = size - total_send;
		actual_send = send(this->fd, (char*)data + total_send, len, MSG_NOSIGNAL);
		if (actual_send < 0){
			throw SocketException("Error en send");
		}
		if (actual_send == 0){
			throw SocketException("Error en send: socket cerrado");
		}
		total_send += actual_send;
	}
	return total_send;
}

int Socket::receive(void* buffer, size_t size){
	size_t total_recv = 0;
	int actual_recv;

	while (total_recv < size){
		int len = size - total_recv;
		actual_recv = recv(this->fd, (char*)buffer + total_recv, len, MSG_NOSIGNAL);
		if (actual_recv < 0){
			throw SocketException("Error en receive");
		}
		if (actual_recv == 0){
			throw SocketException("Error en recv: socket cerrado");
		}
		total_recv += actual_recv;
	}
	return total_recv;
}

Socket Socket::acceptClient(){
	int client = accept(this->fd, NULL, NULL);
	if (client == -1){
		throw SocketException("Error en accept");
	}
	return std::move(Socket(client));
}

void Socket::stop(){
	if (this->fd != -1){
		shutdown(this->fd, SHUT_RDWR);
		close(this->fd);
		this->fd = -1;
	}
}

Socket::Addrinfo::Addrinfo(const char* host, const char* service, int flag){
	//Configuracion para getaddrinfo
	struct addrinfo hints;
	std::memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = AF_INET;  // IPv4
	hints.ai_socktype = SOCK_STREAM;  // TCP
	hints.ai_flags = flag;

	if ((getaddrinfo(host, service, &hints, &this->addrinfo)) != 0){
		throw SocketException("Error en getaddrinfo");
	}
}

Socket Socket::Addrinfo::connectOrBind(int action) const{
	int conection = -1;
	struct addrinfo* res = this->addrinfo;

	while (res != NULL){
		//Recorro todas las direciones posibles hasta que se conecte a una
		Socket sckt(socket(res->ai_family, res->ai_socktype, res->ai_protocol));
		if (sckt.fd != -1){
			if (action == SERVER){
				// Activo la opcion de Reusar la Direccion en caso de que esta
				// no este disponible por un TIME_WAIT
				int val = 1;
				int opt = setsockopt(sckt.fd, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val));
				if (opt != -1){
					conection = bind(sckt.fd, res->ai_addr, res->ai_addrlen);
				}
			} else if (action == CLIENT){
				conection = connect(sckt.fd, res->ai_addr, res->ai_addrlen);
			}
			if (conection != -1){
				return std::move(sckt);  //Conexion correcta
			}
		}
		res = res->ai_next;
	}
	
	throw SocketException("El socket no pudo conectarse");
}

Socket::Addrinfo::~Addrinfo(){
	freeaddrinfo(this->addrinfo);
}

Socket::Server::Server(const char* service, int max_client_wait):
	service(service), max_client_wait(max_client_wait){}
				
Socket::Server::~Server(){}

const char* Socket::Server::getService() const{
	return this->service;
}
				
int Socket::Server::getMaxClientWait() const{
	return this->max_client_wait;
}

Socket::Client::Client(const char* host, const char* service):
	host(host), service(service){}
				
Socket::Client::~Client(){}

const char* Socket::Client::getHost() const{
	return this->host;
}

const char* Socket::Client::getService() const{
	return this->service;
}
