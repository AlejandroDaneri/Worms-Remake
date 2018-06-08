
#ifndef WORMS_INVALIDMAP_H
#define WORMS_INVALIDMAP_H


#include <exception>

// Clase que se encarga de lanzar una excepcion cuando el mapa a guardar es invalido
class InvalidMapError : public std::exception{
private:
    const char* message;
public:
    InvalidMapError(const char *message) noexcept;

    virtual const char *what() const noexcept;

    ~InvalidMapError() override;
};


#endif //WORMS_INVALIDMAP_H
