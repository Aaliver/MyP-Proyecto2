/**
 * @file persona_dao.hpp
 * @brief Definción del objeto de acceso a las personas.
 */
#pragma once

#include <sqlite3.h>

#include "persona.hpp"

/**
 * @class PersonaDao
 * @brief Clase que maneja a las personas de la base de datos.
 * @details Se encarga de realizar las consultas de las personas.
 */
class PersonaDao {

private:

  /* La coneción de la base de datos. */
  sqlite3* conexion;

public:

  /**
   * @brief El constructor.
   */
  explicit PersonaDao(sqlite3* conexion);

  /**
   * @brief Añade una persona a la base de datos.
   * @param persona la persona a añadir.
   */
  void addPersona(const Persona& persona);

  /**
   * @brief Regresa una persona de la base de datos.
   * @param id el identificador de la persona a regresar.
   * @return una persona de la base de datos.
   */
  Persona getPersona(int id) const;

  /**
   * @brief Actualiza una persona en la base de datos.
   * @param persona la persona a actualizar.
   */
  void updatePersona(const Persona& persona);

  /**
   * @brief Elimina una persona de la base de datos.
   * @param id el identificador de la persona a eliminar.
   */
  void deletePersona(int id);
};
