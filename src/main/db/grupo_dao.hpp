/**
 * @file grupo_dao.hpp
 * @brief Definición del objeto de acceso a los grupos.
 */
#pragma once

#include <sqlite3.h>

#include "grupo.hpp"

/**
 * @class GrupoDao
 * @brief Clase que maneja a los grupos de la base de datos.
 * @details Se encarga de realizar las consultas de los grupos.
 */
class GrupoDao {

private:

  /* La conexión de la base de datos. */
  sqlite3* conexion;

public:

  /**
   * @brief El constructor.
   */
  explicit GrupoDao(sqlite3* conexion);

  /**
   * @brief Añade un grupo a la base de datos.
   * @param grupo el grupo a añadir.
   */
  void addGrupo(const Grupo& grupo);

  /**
   * @brief Regresa un grupo de la base de datos.
   * @param id el identificador del grupo a regresar.
   * @return un grupo de la base de datos.
   */
  Grupo getGrupo(int id) const;

  /**
   * @brief Actualiza un grupo en la base de datos.
   * @param grupo el grupo a actualizar.
   */
  void updateGrupo(const Grupo& grupo);

  /**
   * @brief Elimina un grupo de la base de datos.
   * @param id el identificador del grupo a eliminar.
   */
  void deleteGrupo(int id);
};
