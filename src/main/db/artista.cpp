#include "artista.hpp"

void Artista::setId(int id) {
  this->id = id;
}

int Artista::getId() const {
  return id;
}

void Artista::setIdType(int idType) {
  this->idType = idType;
}

int Artista::getIdType() const {
  return idType;
}

void Artista::setName(std::string name) {
  this->name = name;
}

std::string Artista::getName() const {
  return name;
}
