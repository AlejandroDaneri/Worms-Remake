#include <string>
#include "File.h"

const std::string FILE_ERROR("Error al abrir el archivo: ");

File::File(){}

File::File(std::string name, file_mode mode):
	file(name, mode){
		if (!this->file.is_open()){
			throw std::runtime_error(FILE_ERROR + name);
		}
	}

File::~File(){}

void File::write_buffer(const char* buffer, size_t size){
	this->file.write(buffer, size);
}

void File::read_buffer(char* buffer, size_t size){
	this->file.read(buffer, size);
}

std::string File::get_line(){
	std::string line;
	std::getline(this->file, line);
	return std::move(line);
}

size_t File::size(){
	size_t offset = this->file.tellg(); //Guardo el offset actual
	this->file.seekg(0, this->file.end);
    size_t file_length = this->file.tellg();
    this->file.seekg(offset, this->file.beg); //Vuelvo al offset original
    return file_length;
}

size_t File::gcount() const{
	return this->file.gcount();
}

bool File::eof() const{
	return this->file.eof();
}

File::File(File&& other):file(std::move(other.file)){}

File& File::operator=(File&& other){
	if (this != &other){
		this->file = std::move(other.file);
	}
	return *this;
}
