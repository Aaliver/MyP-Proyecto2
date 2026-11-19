/**
 * @file artista.hpp
 * @brief Definición de los artistas.
 */
#pragma once

#include <string>

/**
 * @class Artista
 * @brief Clase para los astistas de la base de datos.
 * @details Guarda los datos de un artista.
 */
class Artista {

private:

  /* El identificador del artista. */
  int id;
  /* El tipo del identificador. */
  int idType;
  /* El nombre del artista. */
  std::string name;

public:

  /**
   * @brief Define el identificador del artista.
   * @param id el identificador del artista.
   */
  void setId(int id);

  /**
   * @brief Regresa el identificador del artista.
   * @return el identificador del artista.
   */
  int getId() const;

  /**
   * @brief Define el tipo del identificador del artista.
   * @param idType el tipo del identificador del artista.
   */
  void setIdType(int idType);

  /**
   * @brief Regresa el tipo del identificador del artista.
   * @return el tipo del identificador del artista.
   */
  int getIdType() const;

  /**
   * @brief Define el nombre del artista.
   * @param name el nombre del artista.
   */
  void setName(std::string name);

  /**
   * @brief Regresa el nombre del artista.
   * @return el nombre del artista.
   */
  std::string getName() const;
};
