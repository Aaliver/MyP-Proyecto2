/**
 * @file minero.hpp
 * @brief Definción del minero.
 */

#pragma once

#include <filesystem>
#include <string>
#include <vector>

#include "rola_dao.hpp"

/**
 * @namespace Minero
 * @brief Funciones para el minero de la base de datos.
 * @details Mina el directorio de entrada y lee la información de los archivos .mp3
 *          que estan en él.
 */
namespace Minero {

  /**
   * @brief Regresa un vector con las rolas que no forman parte de la base de datos.
   * @param ruta la ruta del directorio del que obtener los rolas.
   * @param dao el dao del que obtener las rolas que ya pertenecen a la base de
   *        datos.
   * @return un vector con las rolas que no forman parte de la base de datos.
   */
  std::vector<Rola> mina(std::filesystem::path ruta, RolaDao dao);

  /**
   * @brief Regresa una rola con la información de un .mp3.
   * @param ruta la ruta del mp3 del que obtener la información.
   * @return una rola con la información de un .mp3.
   */
  Rola obtenerRola(std::string ruta);
};
