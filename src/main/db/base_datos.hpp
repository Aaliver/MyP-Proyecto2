/**
 * @file base_datos.hpp
 * @brief Definción de la base de datos.
 */
#pragma once

#include <sqlite3.h>

/**
 * @class BaseDeDatos
 * @brief Clase para la base de datos.
 * @details Mantiene la conexión de la base de datos.
 */
class BaseDeDatos {

private:

  /* La conexión de la base de datos. */
  sqlite3 *conexion;

public:

  /**
   * El constructor.
   */
  BaseDeDatos();

  /**
   * El destructor.
   */
  ~BaseDeDatos();
};
