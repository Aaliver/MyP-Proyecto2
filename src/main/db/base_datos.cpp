#include "base_datos.hpp"

#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <sstream>

namespace fs = std::filesystem;

fs::path ruta_db() {
  const char* xdg = std::getenv("XDG_DATA_HOME");
  fs::path ruta;
  if (xdg && *xdg != '\0') {
    ruta = fs::path(xdg) / "myp-proyecto2";
    fs::create_directories(ruta);
    return ruta / "base_datos.db";
  }

  const char* home = std::getenv("HOME");
  if (!home || *home == '\0')
    return fs::path("base_datos.db");

  ruta = fs::path(home) / ".local" / "share" / "myp-proyecto2";
  fs::create_directories(ruta);
  return ruta / "base_datos.db";
}

std::string sql() {
    std::ifstream archivo("resources/rolas.sql");
    if (!archivo.is_open())
        throw std::runtime_error("No se pudo abrir el archivo SQL.");
    std::stringstream buffer;
    buffer << archivo.rdbuf();
    return buffer.str();
}

BaseDeDatos::BaseDeDatos() : conexion(nullptr) {
  fs::path archivo = ruta_db();
  bool existe = fs::exists(archivo);

  try {
    if (sqlite3_open(archivo.c_str(), &conexion) != SQLITE_OK)
      throw std::runtime_error("Error al abrir la base de datos.");
    if (!existe && sqlite3_exec(conexion, sql().c_str(), nullptr, nullptr, nullptr) != SQLITE_OK)
      throw std::runtime_error("Error al crear las tablas de la base de datos.");
  } catch (const std::runtime_error& re) {
    sqlite3_close_v2(conexion);
    throw;
  }
}

BaseDeDatos::~BaseDeDatos() {
  sqlite3_close_v2(conexion);
}
