/**
 * @file rola.hpp
 * @brief Definición de las rolas.
 */
#pragma once

#include <string>

/**
 * @class Rola
 * @brief Clase para las rolas de la base de datos.
 * @details Guarda los datos de una rola.
 */
class Rola {

private:

  /* El identificador de la rola. */
  int rolaId;
  /* El identificador del artista. */
  int artistId;
  /* El identificador del album. */
  int albumId;
  /* La ruta de la rola. */
  std::string path;
  /* El título de la rola. */
  std::string title;
  /* La pista de la rola. */
  int track;
  /* El año de la rola. */
  int year;
  /* El género de la rola. */
  std::string genre;

public:

  /**
   * Define el identificador de la rola.
   * @param id el identificador de la rola.
   */
  void setRolaId(int id);

  /**
   * Regresa el identificador de la rola.
   * @return el identificador de la rola.
   */
  int getRolaId() const;

  /**
   * Define el identificador del artista.
   * @param id el identificador de artista.
   */
  void setArtistId(int id);

  /**
   * Regresa el identificador del artista.
   * @return el identificador del artista.
   */
  int getArtistId() const;

  /**
   * Define el identificador del album.
   * @param id el identificador del album.
   */
  void setAlbumId(int id);

  /**
   * Regresa el identificador del album.
   * @return el identificador del album.
   */
  int getAlbumId() const;

  /**
   * Define la ruta de la rola.
   * @param path la ruta de la rola.
   */
  void setPath(std::string path);

  /**
   * Regresa la ruta de la rola.
   * @return la ruta de la rola.
   */
  std::string getPath() const;

  /**
   * Define el título de la rola.
   * @param title el título de la rola.
   */
  void setTitle(std::string title);

  /**
   * Regresa el título de la rola.
   * @return el título de la rola.
   */
  std::string getTitle() const;

  /**
   * Define la pista de la rola.
   * @param track la pista de la rola.
   */
  void setTrack(int track);

  /**
   * Regresa la pista de la rola.
   * @return la pista de la rola.
   */
  int getTrack() const;

  /**
   * Define el año de la rola.
   * @param year el año de la rola.
   */
  void setYear(int year);

  /**
   * Regresa el año de la rola.
   * @return el año de la rola.
   */
  int getYear() const;

  /**
   * Define el género de la rola.
   * @param genre el género ruta de la rola.
   */
  void setGenre(std::string genre);

  /**
   * Regresa el género de la rola.
   * @return el género de la rola.
   */
  std::string getGenre() const;
};
