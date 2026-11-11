/**
 * @file elementos.hpp
 * @brief Definición de los elementos nuevos obtenidos al minar.
 */

#pragma once

#include "rola.hpp"
#include "album.hpp"
#include "grupo.hpp"

/**
 * @struct Elementos
 * @brief Estructura para guardas los nuevos elementos de la base de datos.
 */
struct Elementos {

  /**
   * Las rolas nuevas.
   */
  std::vector<Rola> rolasNuevas;

  /**
   * Los albums nuevos.
   */
  std::vector<Album> albumsNuevos;

  /**
   * Los grupos nuevos.
   */
  std::vector<Grupo> gruposNuevos;
}
