#include "rola_dao.hpp"

#include "dao_utils.hpp"

RolaDao::RolaDao(sqlite3* conexion) : conexion(conexion) {}

void RolaDao::addRola(const Rola& rola) {
  sqlite3_stmt* stmt;
  const char* sql = "INSERT INTO rolas (id_rola, id_performer, id_album, path, title, track, year, genre) VALUES (?, ?, ?, ?, ?, ?, ?, ?);";
  if (sqlite3_prepare_v2(conexion, sql, -1, &stmt, nullptr) != SQLITE_OK)
    throw std::runtime_error("Error al preparar la consulta.");
  sqlite3_bind_int(stmt, 1, rola.getRolaId());
  sqlite3_bind_int(stmt, 2, rola.getArtistId());
  sqlite3_bind_int(stmt, 3, rola.getAlbumId());
  sqlite3_bind_text(stmt, 4, rola.getPath().c_str(), -1, SQLITE_TRANSIENT);
  sqlite3_bind_text(stmt, 5, rola.getTitle().c_str(), -1, SQLITE_TRANSIENT);
  sqlite3_bind_int(stmt, 6, rola.getTrack());
  sqlite3_bind_int(stmt, 7, rola.getYear());
  sqlite3_bind_text(stmt, 8, rola.getGenre().c_str(), -1, SQLITE_TRANSIENT);
  if (sqlite3_step(stmt) != SQLITE_DONE)
    DaoUtils::sqliteError(stmt, "Error al añadir el registro.");
  sqlite3_finalize(stmt);
}

Rola RolaDao::getRola(int id) const {
  sqlite3_stmt* stmt;
  const char* sql = "SELECT id_performer, id_album, path, title, track, year, genre FROM rolas WHERE id_rola = ?;";
  if (sqlite3_prepare_v2(conexion, sql, -1, &stmt, nullptr) != SQLITE_OK)
    throw std::runtime_error("Error al preparar la consulta.");
  sqlite3_bind_int(stmt, 1, id);
  if (sqlite3_step(stmt) != SQLITE_ROW)
    DaoUtils::sqliteError(stmt, "Error al obtener el registro.");
  Rola rola;
  rola.setRolaId(id);
  rola.setArtistId(sqlite3_column_int(stmt, 0));
  rola.setAlbumId(sqlite3_column_int(stmt, 1));
  rola.setPath(DaoUtils::castString(stmt, 2));
  rola.setTitle(DaoUtils::castString(stmt, 3));
  rola.setTrack(sqlite3_column_int(stmt, 4));
  rola.setYear(sqlite3_column_int(stmt, 5));
  rola.setGenre(DaoUtils::castString(stmt, 6));
  sqlite3_finalize(stmt);
  return rola;
}

void RolaDao::updateRola(const Rola& rola) {
  sqlite3_stmt* stmt;
  const char* sql = "UPDATE rolas SET id_performer = ?, id_album = ?, path = ?, title = ?, track = ?, year = ?, genre = ? WHERE id_rola = ?;";
  if (sqlite3_prepare_v2(conexion, sql, -1, &stmt, nullptr) != SQLITE_OK)
    throw std::runtime_error("Error al preparar la consulta.");
  sqlite3_bind_int(stmt, 1, rola.getArtistId());
  sqlite3_bind_int(stmt, 2, rola.getAlbumId());
  sqlite3_bind_text(stmt, 3, rola.getPath().c_str(), -1, SQLITE_TRANSIENT);
  sqlite3_bind_text(stmt, 4, rola.getTitle().c_str(), -1, SQLITE_TRANSIENT);
  sqlite3_bind_int(stmt, 5, rola.getTrack());
  sqlite3_bind_int(stmt, 6, rola.getYear());
  sqlite3_bind_text(stmt, 7, rola.getGenre().c_str(), -1, SQLITE_TRANSIENT);
  sqlite3_bind_int(stmt, 8, rola.getRolaId());
  if (sqlite3_step(stmt) != SQLITE_DONE)
    DaoUtils::sqliteError(stmt, "Error al actualizar el registro.");
  sqlite3_finalize(stmt);
}

void RolaDao::deleteRola(int id) {
  sqlite3_stmt* stmt;
  const char* sql = "DELETE FROM rolas WHERE id_rola = ?;";
  if (sqlite3_prepare_v2(conexion, sql, -1, &stmt, nullptr) != SQLITE_OK)
    throw std::runtime_error("Error al preparar la consulta.");
  sqlite3_bind_int(stmt, 1, id);
  if (sqlite3_step(stmt) != SQLITE_DONE)
    DaoUtils::sqliteError(stmt, "Error al eliminar el registro.");
  sqlite3_finalize(stmt);
}

std::vector<Rola> RolaDao::getRolas() const {
  sqlite3_stmt* stmt;
  const char* sql = "SELECT * FROM rolas;";
  if (sqlite3_prepare_v2(conexion, sql, -1, &stmt, nullptr) != SQLITE_OK)
    throw std::runtime_error("Error al preparar la consulta.");
  int rc;
  std::vector<Rola> rolas;
  while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
    Rola rola;
    rola.setRolaId(sqlite3_column_int(stmt, 0));
    rola.setArtistId(sqlite3_column_int(stmt, 1));
    rola.setAlbumId(sqlite3_column_int(stmt, 2));
    rola.setPath(DaoUtils::castString(stmt, 3));
    rola.setTitle(DaoUtils::castString(stmt, 4));
    rola.setTrack(sqlite3_column_int(stmt, 5));
    rola.setYear(sqlite3_column_int(stmt, 6));
    rola.setGenre(DaoUtils::castString(stmt, 7));
    rolas.push_back(rola);
  }
  if (rc != SQLITE_DONE)
    DaoUtils::sqliteError(stmt, "Error al completar la consulta.");
  sqlite3_finalize(stmt);
  return rolas;
}

std::unordered_set<std::string> RolaDao::getRolasPath() const {
  sqlite3_stmt* stmt;
  const char* sql = "SELECT path FROM rolas;";
  if (sqlite3_prepare_v2(conexion, sql, -1, &stmt, nullptr) != SQLITE_OK)
    throw std::runtime_error("Error al preparar la consulta.");
  int rc;
  std::unordered_set<std::string> rolas;
  while ((rc = sqlite3_step(stmt)) == SQLITE_ROW)
    rolas.insert(DaoUtils::castString(stmt, 0));
  if (rc != SQLITE_DONE)
    DaoUtils::sqliteError(stmt, "Error al completar la consulta.");
  sqlite3_finalize(stmt);
  return rolas;
}
