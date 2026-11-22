#include "persona.hpp"

void Persona::setId(int id) {
  this->id = id;
}

int Persona::getId() const {
  return id;
}

void Persona::setStageName(std::string name) {
  stageName = name;
}

std::string Persona::getStageName() const {
  return stageName;
}

void Persona::setRealName(std::string name) {
  realName = name;
}

std::string Persona::getRealName() const {
  return realName;
}

void Persona::setBirthDate(std::string date) {
  birthDate = date;
}

std::string Persona::getBirthDate() const {
  return birthDate;
}

void Persona::setDeathDate(std::string date) {
  deathDate = date;
}

std::string Persona::getDeathDate() const {
  return deathDate;
}
