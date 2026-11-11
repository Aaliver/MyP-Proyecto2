/**
 * @file dao_utils.hpp
 * @brief Definición de las funciones auxiliares de los dao.
 */
#pragma once

#include <sqlite3.h>
#include <string>

/**
 * @namespace DaoUtils
 * @brief Funciones auxiliares para los dao.
 */
namespace DaoUtils {

  /**
   * @brief Regresa el casteo de la cadena que corresponde a una columna de una
   *        consulta SQL.
   * @param stmt el objeto con la consulta sql.
   * @param col la columna del que obtener la cadena.
   * @return la cadena que corresponde a una columna de una consulta SQL.
   */
  std::string castString(sqlite3_stmt* stmt, int col);

  /**
   * @brief Termina una consulta SQL que salio mal.
   * @param stmt el objeto con la consulta sql a terminar.
   * @param mensaje el mensaje de error.
   */
  void sqliteError(sqlite3_stmt* stmt, const std::string mensaje);
};
