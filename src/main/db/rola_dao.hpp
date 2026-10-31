/**
 * @file rola_dao.hpp
 * @brief Definición del objeto de acceso a las rolas.
 */
#pragma once

#include <sqlite3.h>

#include "rola.hpp"

/**
 * @class RolaDao
 * @brief Clase que maneja la base de datos.
 * @details Se encarga de realizar las consultas de las rolas.
 */
class RolaDao {

private:

  /* La conexión de la base de datos. */
  sqlite3 *conexion;

public:

  /**
   * El constructor.
   */
  explicit RolaDao(sqlite3* conexion);

  /**
   * Añade una rola a la base de datos.
   * @param rola la rola a añadir.
   */
  void addRola(const Rola& rola);

  /**
   * Regresa una rola de la base de datos.
   * @param id el identificador de la rola a regresar.
   * @return una rola de la base de datos.
   */
  Rola getRola(int id) const;

  /**
   * Actualiza una rola en la base de datos.
   * @param rola la rola a actualizar.
   */
  void updateRola(const Rola& rola);

  /**
   * Elimina una rola de la base de datos.
   * @param id el identificador de la rola a eliminar.
   */
  void deleteRola(int id);
};
