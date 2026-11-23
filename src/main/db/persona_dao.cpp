#include "persona_dao.hpp"

#include "dao_utils.hpp"

PersonaDao::PersonaDao(sqlite3* conexion) : conexion(conexion) {}

void PersonaDao::addPersona(const Persona& persona) {
  sqlite3_stmt* stmt;
  const char* sql = "INSERT INTO persons (stage_name, real_name, birth_date, death_date) VALUES (?, ?, ?, ?);";
  if (sqlite3_prepare_v2(conexion, sql, -1, &stmt, nullptr) != SQLITE_OK)
    throw std::runtime_error("Error al preparar la consulta.");
  sqlite3_bind_text(stmt, 1, persona.getStageName().c_str(), -1, SQLITE_TRANSIENT);
  sqlite3_bind_text(stmt, 2, persona.getRealName().c_str(), -1, SQLITE_TRANSIENT);
  sqlite3_bind_text(stmt, 3, persona.getBirthDate().c_str(), -1, SQLITE_TRANSIENT);
  sqlite3_bind_text(stmt, 4, persona.getDeathDate().c_str(), -1, SQLITE_TRANSIENT);
  if (sqlite3_step(stmt) != SQLITE_DONE)
    DaoUtils::sqliteError(stmt, "Error al añadir el artista.");
  sqlite3_finalize(stmt);
}

Persona PersonaDao::getPersona(int id) const {
  sqlite3_stmt* stmt;
  const char* sql = "SELECT stage_name, real_name, birth_date, death_date FROM persons WHERE id_person = ?;";
  if (sqlite3_prepare_v2(conexion, sql, -1, &stmt, nullptr) != SQLITE_OK)
    throw std::runtime_error("Error al preparar la consulta.");
  sqlite3_bind_int(stmt, 1, id);
  if (sqlite3_step(stmt) != SQLITE_ROW)
    DaoUtils::sqliteError(stmt, "Error al obtener el registro.");
  Persona persona;
  persona.setStageName(DaoUtils::castString(stmt, 0));
  persona.setRealName(DaoUtils::castString(stmt, 1));
  persona.setBirthDate(DaoUtils::castString(stmt, 2));
  persona.setDeathDate(DaoUtils::castString(stmt, 3));
  sqlite3_finalize(stmt);
  return persona;
}

void PersonaDao::updatePersona(const Persona& persona) {
  sqlite3_stmt* stmt;
  const char* sql = "UPDATE persons SET stage_name = ?, real_name = ?, birth_date = ?, death_date = ? WHERE id_person = ?;";
  if (sqlite3_prepare_v2(conexion, sql, -1, &stmt, nullptr) != SQLITE_OK)
    throw std::runtime_error("Error al preparar la consulta.");
  sqlite3_bind_text(stmt, 1, persona.getStageName().c_str(), -1, SQLITE_TRANSIENT);
  sqlite3_bind_text(stmt, 2, persona.getRealName().c_str(), -1, SQLITE_TRANSIENT);
  sqlite3_bind_text(stmt, 3, persona.getBirthDate().c_str(), -1, SQLITE_TRANSIENT);
  sqlite3_bind_text(stmt, 4, persona.getDeathDate().c_str(), -1, SQLITE_TRANSIENT);
  if (sqlite3_step(stmt) != SQLITE_DONE)
    DaoUtils::sqliteError(stmt, "Error al actualizar el registro.");
  sqlite3_finalize(stmt);
}

void PersonaDao::deletePersona(int id) {
  sqlite3_stmt* stmt;
  const char* sql = "DELETE FROM persons WHERE id_person = ?;";
  if (sqlite3_prepare_v2(conexion, sql, -1, &stmt, nullptr) != SQLITE_OK)
    throw std::runtime_error("Error al preparar la consulta.");
  sqlite3_bind_int(stmt, 1, id);
  if (sqlite3_step(stmt) != SQLITE_DONE)
    DaoUtils::sqliteError(stmt, "Error al eliminar el registro.");
  sqlite3_finalize(stmt);
}
