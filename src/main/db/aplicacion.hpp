/**
 * @file aplicacion.hpp
 * @brief Definición de la aplicación.
 */

#pragma once
#include <string>
#include <filesystem>
#include "QQmlApplicationEngine"

/**
 * @class Aplicacion
 * @brief Clase para la aplicación de la Base de Datos.
 * @details Verifica que los argumentos de entrada sean válidos e inicia la
 *          aplicación.
 */
class Aplicacion {

public:

  /**
   * El constructor.
   * @param argc la cantidad de entradas.
   * @param argv el arreglo con las entradas.
   */
  Aplicacion(int argc, char* argv[]);

  /**
   * @brief Ejecuta la aplicación.
   */
  int ejecuta();

private:

  /* La ruta de entrada. */
  std::filesystem::path ruta;
  /* El motor. */
  QQmlApplicationEngine engine;

  /* Verifica que las entradas sean válidas. */
  void valida(int argc, char* argv[]);

  /* Verifica que la ruta sea válida. */
  void validaRuta(std::string ruta);
};
