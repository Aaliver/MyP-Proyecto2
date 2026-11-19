/**
 * @file elementos.hpp
 * @brief Definición de los elementos nuevos obtenidos al minar.
 */

#pragma once

#include <vector>

#include "rola.hpp"
#include "album.hpp"
#include "artista.hpp"

/**
 * @struct Elementos
 * @brief Estructura para guardas los nuevos elementos de la base de datos.
 */
struct Elementos {

  /**
   * @brief Las rolas nuevas.
   */
  std::vector<Rola> rolasNuevas;

  /**
   * @brief Los albums nuevos.
   */
  std::vector<Album> albumsNuevos;

  /**
   * @brief Los artistas nuevos.
   */
  std::vector<Artista> artistasNuevos;
};
