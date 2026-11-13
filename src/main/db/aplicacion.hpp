/**
 * @file aplicacion.hpp
 * @brief Definición de la aplicación.
 */
#pragma once

#include <filesystem>
#include <string>

#include <QQmlApplicationEngine>

#include "controlador.hpp"

/**
 * @class Aplicacion
 * @brief Clase para la aplicación de la Base de Datos.
 * @details Verifica que los argumentos de entrada sean válidos e inicia la
 *          aplicación.
 */
class Aplicacion {

private:

  /* El motor. */
  QQmlApplicationEngine engine;
  /* El controlador. */
  Controlador controlador;

  /* Verifica que las entradas sean válidas. */
  std::filesystem::path valida(int argc, char* argv[]);

  /* Verifica que la ruta sea válida. */
  std::filesystem::path validaRuta(std::string ruta);

public:

  /**
   * @brief El constructor.
   * @param argc la cantidad de entradas.
   * @param argv el arreglo con las entradas.
   */
  Aplicacion(int argc, char* argv[]);

  /**
   * @brief Ejecuta la aplicación.
   */
  int ejecuta();
};
