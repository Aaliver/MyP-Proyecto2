/**
 * @file rola_dao.hpp
 * @brief Definición del objeto de acceso a las rolas.
 */
#pragma once

#include <sqlite3.h>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "param_rola.hpp"
#include "rola.hpp"
#include "rola_nueva.hpp"
#include "vista_rola.hpp"

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
   * @brief Añade rolas a la base de datos.
   * @param rolas el vector con las rolas a añadir.
   * @param albums los albums de las rolas a añadir.
   */
  void addRolas(const std::vector<RolaNueva>& rolas,
		std::unordered_map<std::string, int> albums);

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
   * @brief Regresa un vector con las rolas de la base de datos que cumplen ciertos
   *        criterios junto con sus álbumes y sus artistas.
   * @param param los criterios a cumplir.
   * @return un vector con las rolas de la base de datos que cumplen los criterios.
   */
  std::vector<VistaRola> searchRolas(const ParamRola& param) const;

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

  /**
   * @brief Regresa un vector con las rolas de la base de datos junto con sus
   *        álbumes y sus artistas.
   * @return un vector con todas rolas.
   */
  std::vector<VistaRola> getRolasView() const;
};
