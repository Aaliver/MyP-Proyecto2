#include "album_dao.hpp"

#include "dao_utils.hpp"

AlbumDao::AlbumDao(sqlite3* conexion) : conexion(conexion) {}

void AlbumDao::addAlbums(const std::vector<Album>& albums) {
  sqlite3_stmt* stmt;
  const char* sql = "INSERT INTO albums (path, name, year) VALUES (?, ?, ?);";
  if (sqlite3_prepare_v2(conexion, sql, -1, &stmt, nullptr) != SQLITE_OK)
    throw std::runtime_error("Error al preparar la consulta.");
  for (const auto& album: albums) {
    sqlite3_bind_text(stmt, 1, album.getPath().c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, album.getName().c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 3, album.getYear());
    if (sqlite3_step(stmt) != SQLITE_DONE)
      DaoUtils::sqliteError(stmt, "Error al añadir el registro.");
    sqlite3_reset(stmt);
    sqlite3_clear_bindings(stmt);
  }
  sqlite3_finalize(stmt);
}

Album AlbumDao::getAlbum(int id) const {
  sqlite3_stmt* stmt;
  const char* sql = "SELECT path, name, year FROM albums WHERE id_album = ?;";
  if (sqlite3_prepare_v2(conexion, sql, -1, &stmt, nullptr) != SQLITE_OK)
    throw std::runtime_error("Error al preparar la consulta.");
  sqlite3_bind_int(stmt, 1, id);
  if (sqlite3_step(stmt) != SQLITE_ROW)
    DaoUtils::sqliteError(stmt, "Error al obtener el registro.");
  Album album;
  album.setId(id);
  album.setPath(DaoUtils::castString(stmt, 0));
  album.setName(DaoUtils::castString(stmt, 1));
  album.setYear(sqlite3_column_int(stmt, 2));
  sqlite3_finalize(stmt);
  return album;
}

void AlbumDao::updateAlbum(const Album& album) {
  sqlite3_stmt* stmt;
  const char* sql = "UPDATE albums SET path = ?, name = ?, year = ? WHERE id_album = ?;";
  if (sqlite3_prepare_v2(conexion, sql, -1, &stmt, nullptr) != SQLITE_OK)
    throw std::runtime_error("Error al preparar la consulta.");
  sqlite3_bind_text(stmt, 1, album.getPath().c_str(), -1, SQLITE_TRANSIENT);
  sqlite3_bind_text(stmt, 2, album.getName().c_str(), -1, SQLITE_TRANSIENT);
  sqlite3_bind_int(stmt, 3, album.getYear());
  sqlite3_bind_int(stmt, 4, album.getId());
  if (sqlite3_step(stmt) != SQLITE_DONE)
    DaoUtils::sqliteError(stmt, "Error al actualizar el registro.");
  sqlite3_finalize(stmt);
}

void AlbumDao::deleteAlbum(int id) {
  sqlite3_stmt* stmt;
  const char* sql = "DELETE FROM albums WHERE id_album = ?;";
  if (sqlite3_prepare_v2(conexion, sql, -1, &stmt, nullptr) != SQLITE_OK)
    throw std::runtime_error("Error al preparar la consulta.");
  sqlite3_bind_int(stmt, 1, id);
  if (sqlite3_step(stmt) != SQLITE_DONE)
    DaoUtils::sqliteError(stmt, "Error al eliminar el registro.");
  sqlite3_finalize(stmt);
}

std::unordered_set<std::string> AlbumDao::getAlbumsPath() const {
  sqlite3_stmt* stmt;
  const char* sql = "SELECT path FROM albums;";
  if (sqlite3_prepare_v2(conexion, sql, -1, &stmt, nullptr) != SQLITE_OK)
    throw std::runtime_error("Error al preparar la consulta.");
  int rc;
  std::unordered_set<std::string> albums;
  while ((rc = sqlite3_step(stmt)) == SQLITE_ROW)
    albums.insert(DaoUtils::castString(stmt, 0));
  if (rc != SQLITE_DONE)
    DaoUtils::sqliteError(stmt, "Error al completar la consulta.");
  sqlite3_finalize(stmt);
  return albums;
}
