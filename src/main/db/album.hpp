/**
 * @file album.hpp
 * @brief Definición de los albums.
 */
#pragma once

#include <string>

/**
 * @class Album
 * @brief Clase para los albums de la base de datos.
 * @details Guarda los datos de un album.
 */
class Album {

private:

  /* El identificador del album. */
  int id;
  /* La ruta del album. */
  std::string path;
  /* El nombre del album. */
  std::string name;
  /* El año del album. */
  int year;

public:

  /**
   * Define el identificador del album.
   * @param id el identificador del album.
   */
  void setId(int id);

  /**
   * Regresa el identificador del album.
   * @return el identificador del album.
   */
  int getId() const;

  /**
   * Define la ruta del album.
   * @param path la ruta del album.
   */
  void setPath(std::string path);

  /**
   * Regresa la ruta del album.
   * @return la ruta del album.
   */
  std::string getPath() const;

  /**
   * Define el nombre del album.
   * @param name el nombre del album.
   */
  void setName(std::string name);

  /**
   * Regresa el nombre del album.
   * @return el nombre del album.
   */
  std::string getName() const;

  /**
   * Define el año del album.
   * @param year el año del album.
   */
  void setYear(int year);

  /**
   * Regresa el año del album.
   * @return el año del album.
   */
  int getYear() const;
};
