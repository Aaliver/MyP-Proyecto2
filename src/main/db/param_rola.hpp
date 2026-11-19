/**
 * @file param_rola.hpp
 * @brief Definición de los parámetros de búsqueda de una rola.
 */
#pragma once

#include <optional>
#include <string>

/**
 * @struct ParamRola
 * @brief Estructura para guardar los parámetros de búsqueda de una rola.
 */
struct ParamRola {

  /**
   * @brief El titulo opcional a buscar.
   */
  std::optional<std::string> title;

  /**
   * @brief El año opcional a buscar.
   */
  std::optional<int> year;

  /**
   * @brief El género opcional a buscar.
   */
  std::optional<std::string> genre;

  /**
   * @brief El album opcional a buscar.
   */
  std::optional<std::string> album;

  /**
   * @brief El artista opcional a buscar.
   */
  std::optional<std::string> artist;
};
