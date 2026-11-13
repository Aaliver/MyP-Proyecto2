/**
 * @file rola_dao.hpp
 * @brief Definición del objeto de acceso a las rolas.
 */
#pragma once

#include <sqlite3.h>
#include <unordered_set>
#include <vector>

#include "rola.hpp"

/**
 * @class RolaDao
 * @brief Clase que maneja las rolas de la base de datos.
 * @details Se encarga de realizar las consultas de las rolas.
 */
class RolaDao {

private:

  /* La conexión de la base de datos. */
  sqlite3* conexion;

public:

  /**
   * @brief El constructor.
   */
  explicit RolaDao(sqlite3* conexion);

  /**
   * @brief Añade una rola a la base de datos.
   * @param rola la rola a añadir.
   */
  void addRola(const Rola& rola);

  /**
   * @brief Regresa una rola de la base de datos.
   * @param id el identificador de la rola a regresar.
   * @return una rola de la base de datos.
   */
  Rola getRola(int id) const;

  /**
   * @brief Actualiza una rola en la base de datos.
   * @param rola la rola a actualizar.
   */
  void updateRola(const Rola& rola);

  /**
   * @brief Elimina una rola de la base de datos.
   * @param id el identificador de la rola a eliminar.
   */
  void deleteRola(int id);

  /**
   * @brief Regresa un vector con las rolas de la base de datos.
   * @return un vector con todas las rolas.
   */
  std::vector<Rola> getRolas() const;

  /**
   * @brief Regresa un conjunto con las rutas de las rolas de la base de datos.
   * @return un conjunto con las rutas de todas las rolas.
   */
  std::unordered_set<std::string> getRolasPath() const;
};
