/**
 * @file controlador.hpp
 * @brief Definición del controlador.
 */
#pragma once

#include <QObject>
#include <filesystem>

/**
 * @class Controlador
 * @brief Clase para el controlador de la base de datos.
 * @details Se encarga de la comunicación entre el modelo y la vista.
 */
class Controlador : public QObject {
  Q_OBJECT

private:

  /* La ruta del directorio a minar. */
  std::filesystem::path ruta;

public:

  /**
   * @brief El constructor.
   */
  explicit Controlador(std::filesystem::path ruta, QObject* parent = nullptr);

  /**
   * @brief Mina el directorio y muestra los resultados.
   */
  Q_INVOKABLE void minar();
};
