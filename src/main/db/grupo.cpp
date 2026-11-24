#include "grupo.hpp"

void Grupo::setId(int id) {
  this->id = id;
}

int Grupo::getId() const {
  return id;
}

void Grupo::setName(std::string name) {
  this->name = name;
}

std::string Grupo::getName() const {
  return name;
}

void Grupo::setStartDate(std::string date) {
  startDate = date;
}

std::string Grupo::getStartDate() const {
  return startDate;
}

void Grupo::setEndDate(std::string date) {
  endDate = date;
}

std::string Grupo::getEndDate() const {
  return endDate;
}
