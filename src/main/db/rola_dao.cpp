#include "rola_dao.hpp"

#include "dao_utils.hpp"

RolaDao::RolaDao(sqlite3* conexion) : conexion(conexion) {}

void RolaDao::addRolas(const std::vector<RolaNueva>& rolas,
		       std::unordered_map<std::string, int> albums) {
  sqlite3_stmt* stmt;
  const char* sql = "INSERT INTO rolas (id_performer, id_album, path, title, track, year, genre) VALUES (?, ?, ?, ?, ?, ?, ?);";
  if (sqlite3_prepare_v2(conexion, sql, -1, &stmt, nullptr) != SQLITE_OK)
    throw std::runtime_error("Error al preparar la consulta.");
  for (const auto& nueva: rolas) {
    sqlite3_bind_int(stmt, 1, nueva.rola.getArtistId());
    sqlite3_bind_int(stmt, 2, albums.at(nueva.albumPath));
    sqlite3_bind_text(stmt, 3, nueva.rola.getPath().c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 4, nueva.rola.getTitle().c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 5, nueva.rola.getTrack());
    sqlite3_bind_int(stmt, 6, nueva.rola.getYear());
    sqlite3_bind_text(stmt, 7, nueva.rola.getGenre().c_str(), -1, SQLITE_TRANSIENT);
    if (sqlite3_step(stmt) != SQLITE_DONE)
      DaoUtils::sqliteError(stmt, "Error al añadir el registro.");
    sqlite3_reset(stmt);
    sqlite3_clear_bindings(stmt);
  }
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

std::vector<VistaRola> RolaDao::searchRolas(const ParamRola& param) const {
  sqlite3_stmt* stmt;
  std::string sql = "SELECT r.*, a.name, p.name FROM rolas r LEFT JOIN albums a ON a.id_album = r.id_album LEFT JOIN performers p ON p.id_performer = r.id_performer WHERE 1 = 1";
  if (param.title.has_value())
    sql += " AND r.title LIKE ?";
  if (param.year.has_value())
    sql += " AND r.year = ?";
  if (param.genre.has_value())
    sql += " AND r.genre LIKE ?";
  if (param.album.has_value())
    sql += " AND a.name LIKE ?";
  if (param.artist.has_value())
    sql += " AND p.name LIKE ?";
  sql += ";";
  if (sqlite3_prepare_v2(conexion, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK)
    throw std::runtime_error("Error al preparar la consulta.");
  int index = 1;
  if (param.title.has_value()) {
    std::string title = "%" + param.title.value() + "%";
    sqlite3_bind_text(stmt, index++, title.c_str(), -1, SQLITE_TRANSIENT);
  }
  if (param.year.has_value())
    sqlite3_bind_int(stmt, index++, param.year.value());
  if (param.genre.has_value()) {
    std::string genre = "%" + param.genre.value() + "%";
    sqlite3_bind_text(stmt, index++, genre.c_str(), -1, SQLITE_TRANSIENT);
  }
  if (param.album.has_value()) {
    std::string album = "%" + param.album.value() + "%";
    sqlite3_bind_text(stmt, index++, album.c_str(), -1, SQLITE_TRANSIENT);
  }
  if (param.artist.has_value()) {
    std::string artist = "%" + param.artist.value() + "%";
    sqlite3_bind_text(stmt, index++, artist.c_str(), -1, SQLITE_TRANSIENT);
  }
  int rc;
  std::vector<VistaRola> rolas;
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
    VistaRola vista;
    vista.rola = rola;
    vista.album = DaoUtils::castString(stmt, 8);
    vista.artista = DaoUtils::castString(stmt, 9);
    rolas.push_back(vista);
  }
  if (rc != SQLITE_DONE)
    DaoUtils::sqliteError(stmt, "Error al completar la consulta.");
  sqlite3_finalize(stmt);
  return rolas;
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

std::vector<VistaRola> RolaDao::getRolasView() const {
  sqlite3_stmt* stmt;
  const char* sql = "SELECT r.*, a.name, p.name FROM rolas r LEFT JOIN albums a ON a.id_album = r.id_album LEFT JOIN performers p ON p.id_performer = r.id_performer;";
  if (sqlite3_prepare_v2(conexion, sql, -1, &stmt, nullptr) != SQLITE_OK)
    throw std::runtime_error("Error al preparar la consulta.");
  int rc;
  std::vector<VistaRola> rolas;
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
    VistaRola vista;
    vista.rola = rola;
    vista.album = DaoUtils::castString(stmt, 8);
    vista.artista = DaoUtils::castString(stmt, 9);
    rolas.push_back(vista);
  }
  if (rc != SQLITE_DONE)
    DaoUtils::sqliteError(stmt, "Error al completar la consulta.");
  sqlite3_finalize(stmt);
  return rolas;
}
