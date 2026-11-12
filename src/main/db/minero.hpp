/**
 * @file minero.hpp
 * @brief Definción del minero.
 */

#pragma once

#include <filesystem>
#include <string>

#include "elementos.hpp"
#include "album_dao.hpp"
#include "artista_dao.hpp"
#include "rola_dao.hpp"

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
   * @param rolaDao el dao del que obtener las rolas que ya pertenecen a la base de
   *        datos.
   * @param albumDao el dao del que obtener los albums que ya pertenecen a la base de
   *        datos.
   * @param artistaDao el dao del que obtener los artistas que ya pertenecen a la base
   *        de datos.
   * @return los elementos que no forman parte de la base de datos.
   */
  Elementos mina(std::filesystem::path ruta, const RolaDao& rolaDao,
		 const AlbumDao& albumDao, const ArtistaDao& artistaDao);
};
