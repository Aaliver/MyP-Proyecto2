#include "grupo_dao.hpp"

#include "dao_utils.hpp"

GrupoDao::GrupoDao(sqlite3* conexion) : conexion(conexion){}

void GrupoDao::addGrupo(const Grupo& grupo) {
  sqlite3_stmt* stmt;
  const char* sql = "INSERT INTO groups (name, start_date, end_date) VALUES (?, ?, ?);";
  if (sqlite3_prepare_v2(conexion, sql, -1, &stmt, nullptr) != SQLITE_OK)
    throw std::runtime_error("Error al preparar la consulta.");
  sqlite3_bind_text(stmt, 1, grupo.getName().c_str(), -1, SQLITE_TRANSIENT);
  sqlite3_bind_text(stmt, 2, grupo.getStartDate().c_str(), -1, SQLITE_TRANSIENT);
  sqlite3_bind_text(stmt, 3, grupo.getEndDate().c_str(), -1, SQLITE_TRANSIENT);
  if (sqlite3_step(stmt) != SQLITE_DONE)
    DaoUtils::sqliteError(stmt, "Error al añadir el grupo.");
  sqlite3_finalize(stmt);
}

Grupo GrupoDao::getGrupo(int id) const {
  sqlite3_stmt* stmt;
  const char* sql = "SELECT name, start_date, end_date FROM groups WHERE id_group = ?;";
  if (sqlite3_prepare_v2(conexion, sql, -1, &stmt, nullptr) != SQLITE_OK)
    throw std::runtime_error("Error al preparar la consulta.");
  sqlite3_bind_int(stmt, 1, id);
  if (sqlite3_step(stmt) != SQLITE_ROW)
    DaoUtils::sqliteError(stmt, "Error al obtener el grupo.");
  Grupo grupo;
  grupo.setName(DaoUtils::castString(stmt, 0));
  grupo.setStartDate(DaoUtils::castString(stmt, 1));
  grupo.setEndDate(DaoUtils::castString(stmt, 2));
  sqlite3_finalize(stmt);
  return grupo;
}

void GrupoDao::updateGrupo(const Grupo& grupo) {
  sqlite3_stmt* stmt;
  const char* sql = "UPDATE groups SET name = ?, start_date = ?, end_date = ? WHERE id_group = ?;";
  if (sqlite3_prepare_v2(conexion, sql, -1, &stmt, nullptr) != SQLITE_OK)
    throw std::runtime_error("Error al preparar la consulta.");
  sqlite3_bind_text(stmt, 1, grupo.getName().c_str(), -1, SQLITE_TRANSIENT);
  sqlite3_bind_text(stmt, 2, grupo.getStartDate().c_str(), -1, SQLITE_TRANSIENT);
  sqlite3_bind_text(stmt, 3, grupo.getEndDate().c_str(), -1, SQLITE_TRANSIENT);
  sqlite3_bind_int(stmt, 4, grupo.getId());
  if (sqlite3_step(stmt) != SQLITE_DONE)
    DaoUtils::sqliteError(stmt, "Error al actualizar el grupop.");
  sqlite3_finalize(stmt);
}

void GrupoDao::deleteGrupo(int id) {
  sqlite3_stmt* stmt;
  const char* sql = "DELETE FROM groups WHERE id_group = ?;";
  if (sqlite3_prepare_v2(conexion, sql, -1, &stmt, nullptr) != SQLITE_OK)
    throw std::runtime_error("Error al preparar la consulta.");
  sqlite3_bind_int(stmt, 1, id);
  if (sqlite3_step(stmt) != SQLITE_DONE)
    DaoUtils::sqliteError(stmt, "Error al eliminar el grupo.");
  sqlite3_finalize(stmt);
}
