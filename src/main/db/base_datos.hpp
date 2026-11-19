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
  sqlite3* conexion;

public:

  /**
   * @brief El constructor.
   * @details Abre la conexión a la base de datos.
   */
  BaseDeDatos();

  /**
   * @brief El destructor.
   * @details Cierra la conexión a la base de datos.
   */
  ~BaseDeDatos();

  /**
   * @return Regresa la conexión a la base de datos.
   * @return la conexión a la base de datos.
   */
  sqlite3* getConexion() const;
};
