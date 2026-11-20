/**
 * @file rola_nueva.hpp
 * @brief Definición de los datos de una rola nueva.
 */
#pragma once

#include <string>

#include "rola.hpp"

/**
 * @struct RolaNueva
 * @brief Estructura para guardar los datos de una rola nueva.
 */
struct RolaNueva {

  /**
   * @brief La rola nueva.
   */
  Rola rola;

  /**
   * @brief La ruta del álbum de la rola nueva.
   */
  std::string albumPath;
};
