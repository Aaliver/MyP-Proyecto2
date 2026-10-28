/**
 * @file minero.hpp
 * @brief Definción del minero.
 */

#pragma once

#include <filesystem>
#include <string>
#include <vector>

/**
 * @namespace Minero
 * @brief Funciones para el minero de la base de datos.
 * @details Mina el directorio de entrada y devuelve las rutas de los mp3.
 */
namespace Minero {

  /**
   * @brief Regresa un vector con las rutas de los archivos .mp3 en el directorio.
   * @param ruta la ruta del directorio.
   * @return un vector con las rutas de los archivos .mp3 en el directorio.
   */
  std::vector<std::string> mina(std::filesystem::path ruta);
};
