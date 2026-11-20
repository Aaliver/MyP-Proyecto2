/**
 * @file vista_rola.hpp
 * @brief Definición de los datos de visualización una rola.
 */
#pragma once

#include <string>

#include "rola.hpp"

/**
 * @struct VistaRola
 * @brief Estructura para guardar los datos de visualización de una rola,
 */
struct VistaRola {

  /**
   * @brief Los datos de la rola.
   */
  Rola rola;

  /**
   * @brief El nombre del album de la rola.
   */
  std::string album;

  /**
   * @brief El nombre del artista de la rola.
   */
  std::string artista;
};
