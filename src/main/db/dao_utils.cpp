#include "dao_utils.hpp"

std::string DaoUtils::castString(sqlite3_stmt* stmt, int col) {
  const char* text = reinterpret_cast<const char*>(sqlite3_column_text(stmt, col));
  return (text != nullptr) ? text : "";
}

void DaoUtils::sqliteError(sqlite3_stmt* stmt, const std::string mensaje) {
  sqlite3_finalize(stmt);
  throw std::runtime_error(mensaje);
}
