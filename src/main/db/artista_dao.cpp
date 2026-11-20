#include "artista_dao.hpp"

#include "dao_utils.hpp"

ArtistaDao::ArtistaDao(sqlite3* conexion) : conexion(conexion) {}

std::unordered_map<std::string, int>
ArtistaDao::addArtistas(const std::vector<Artista>& artistas) {
  sqlite3_stmt* stmt;
  const char* sql = "INSERT INTO performers (id_type, name) VALUES (?, ?);";
  if (sqlite3_prepare_v2(conexion, sql, -1, &stmt, nullptr) != SQLITE_OK)
    throw std::runtime_error("Error al preparar la consulta.");
  std::unordered_map<std::string, int> artistasAgregados;
  for (const auto& artista: artistas) {
    std::string name = artista.getName();
    sqlite3_bind_int(stmt, 1, artista.getIdType());
    sqlite3_bind_text(stmt, 2, name.c_str(), -1, SQLITE_TRANSIENT);
    if (sqlite3_step(stmt) != SQLITE_DONE)
      DaoUtils::sqliteError(stmt, "Error al añadir el artista.");
    int id = static_cast<int>(sqlite3_last_insert_rowid(conexion));
    artistasAgregados.insert({name, id});
    sqlite3_reset(stmt);
    sqlite3_clear_bindings(stmt);
  }
  sqlite3_finalize(stmt);
  return artistasAgregados;
}

Artista ArtistaDao::getArtista(int id) const {
  sqlite3_stmt* stmt;
  const char* sql = "SELECT id_type, name FROM performers WHERE id_performer = ?;";
  if (sqlite3_prepare_v2(conexion, sql, -1, &stmt, nullptr) != SQLITE_OK)
    throw std::runtime_error("Error al preparar la consulta.");
  sqlite3_bind_int(stmt, 1, id);
  if (sqlite3_step(stmt) != SQLITE_ROW)
    DaoUtils::sqliteError(stmt, "Error al obtener el registro.");
  Artista artista;
  artista.setId(id);
  artista.setIdType(sqlite3_column_int(stmt, 0));
  artista.setName(DaoUtils::castString(stmt, 1));
  sqlite3_finalize(stmt);
  return artista;
}

void ArtistaDao::updateArtista(const Artista& artista) {
  sqlite3_stmt* stmt;
  const char* sql = "UPDATE performers SET id_type = ?, name = ? WHERE id_performer = ?;";
  if (sqlite3_prepare_v2(conexion, sql, -1, &stmt, nullptr) != SQLITE_OK)
    throw std::runtime_error("Error al preparar la consulta.");
  sqlite3_bind_int(stmt, 1, artista.getIdType());
  sqlite3_bind_text(stmt, 2, artista.getName().c_str(), -1, SQLITE_TRANSIENT);
  sqlite3_bind_int(stmt, 3, artista.getId());
  if (sqlite3_step(stmt) != SQLITE_DONE)
    DaoUtils::sqliteError(stmt, "Error al actualizar el registro.");
  sqlite3_finalize(stmt);
}

void ArtistaDao::deleteArtista(int id) {
  sqlite3_stmt* stmt;
  const char* sql = "DELETE FROM performers WHERE id_performer = ?;";
  if (sqlite3_prepare_v2(conexion, sql, -1, &stmt, nullptr) != SQLITE_OK)
    throw std::runtime_error("Error al preparar la consulta.");
  sqlite3_bind_int(stmt, 1, id);
  if (sqlite3_step(stmt) != SQLITE_DONE)
    DaoUtils::sqliteError(stmt, "Error al eliminar el registro.");
  sqlite3_finalize(stmt);
}

std::unordered_map<std::string, int> ArtistaDao::getArtistasIds() const {
  sqlite3_stmt* stmt;
  const char* sql = "SELECT id_performer, name FROM performers;";
  if (sqlite3_prepare_v2(conexion, sql, -1, &stmt, nullptr) != SQLITE_OK)
    throw std::runtime_error("Error al preparar la consulta.");
  int rc;
  std::unordered_map<std::string, int> artistas;
  while ((rc = sqlite3_step(stmt)) == SQLITE_ROW)
    artistas.insert({DaoUtils::castString(stmt, 1), sqlite3_column_int(stmt, 0)});
  if (rc != SQLITE_DONE)
    DaoUtils::sqliteError(stmt, "Error al completar la consulta.");
  sqlite3_finalize(stmt);
  return artistas;
}
