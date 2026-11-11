#include "album.hpp"

void Album::setAlbumId(int id) {
  this->id = id;
}

int Album::getAlbumId() const {
  return id;
}

void Album::setPath(std::string path) {
  this->path = path;
}

std::string Album::getPath() const {
  return path;
}

void Album::setName(std::string name) {
  this->name = name;
}

std::string Album::getName() const {
  return name;
}

void Album::setYear(int year) {
  this->year = year;
}

int Album::getYear() const {
  return year;
}
