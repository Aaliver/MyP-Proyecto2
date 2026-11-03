#include "rola.hpp"

void Rola::setRolaId(int id) {
  rolaId = id;
}

int Rola::getRolaId() const {
  return rolaId;
}

void Rola::setArtistId(int id) {
  artistId = id;
}

int Rola::getArtistId() const {
  return artistId;
}

void Rola::setAlbumId(int id) {
  albumId = id;
}

int Rola::getAlbumId() const {
  return albumId;
}

void Rola::setPath(std::string path) {
  this->path = path;
}

std::string Rola::getPath() const {
  return path;
}

void Rola::setTitle(std::string title) {
  this->title = title;
}

std::string Rola::getTitle() const {
  return title;
}

void Rola::setTrack(int track) {
  this->track = track;
}

int Rola::getTrack() const {
  return track;
}

void Rola::setYear(int year) {
  this->year = year;
}

int Rola::getYear() const {
  return year;
}

void Rola::setGenre(std::string genre) {
  this->genre = genre;
}

std::string Rola::getGenre() const {
  return genre;
}
