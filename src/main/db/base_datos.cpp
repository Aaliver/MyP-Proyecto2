#include "base_datos.hpp"

#include <filesystem>

namespace fs = std::filesystem;

fs::path ruta() {
  const char* xdg = std::getenv("XDG_DATA_HOME");
  fs::path ruta;
  if (xdg && *xdg != '\0') {
    ruta = fs::path(xdg) / "proyecto2-myp";
    fs::create_directories(ruta);
    return ruta / "base_datos.db";
  }

  const char* home = std::getenv("HOME");
  if (!home || *home == '\0')
    return fs::path("base_datos.db");

  ruta = fs::path(home) / ".local" / "share" / "proyecto2-myp";
  fs::create_directories(ruta);
  return ruta / "base_datos.db";
}

BaseDeDatos::BaseDeDatos() {
  if (sqlite3_open(ruta().c_str(), &conexion) == SQLITE_OK)
    return;
  sqlite3_close(conexion);
  throw std::runtime_error("Error al abrir la base de datos.");
}

BaseDeDatos::~BaseDeDatos() {
  sqlite3_close_v2(conexion);
}
