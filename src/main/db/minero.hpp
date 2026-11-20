/**
 * @file minero.hpp
 * @brief Definción del minero.
 */
#pragma once

#include <filesystem>
#include <string>
#include <unordered_map>
#include <unordered_set>

#include "elementos.hpp"

/**
 * @namespace Minero
 * @brief Funciones para el minero de la base de datos.
 * @details Mina el directorio de entrada y lee la información de los archivos .mp3
 *          que estan en él.
 */
namespace Minero {

  /**
   * @brief Regresa los elementos que no forman parte de la base de datos.
   * @param ruta la ruta del directorio del que obtener los elementos.
   * @param rolas las rolas que ya pertenecen a la base de datos.
   * @param albums los albums que ya pertenecen a la base de datos.
   * @param artistas los artistas que ya pertenecen a la base de datos.
   * @return los elementos que no forman parte de la base de datos.
   */
  Elementos mina(std::filesystem::path ruta, std::unordered_set<std::string>& rolas,
		 std::unordered_map<std::string, int>& albums,
		 std::unordered_map<std::string, int>& artistas);
};
