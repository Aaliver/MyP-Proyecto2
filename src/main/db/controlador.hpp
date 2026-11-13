/**
 * @file controlador.hpp
 * @brief Definición del controlador.
 */
#pragma once

#include <filesystem>

#include <QObject>
#include <QVariantList>

#include "album_dao.hpp"
#include "artista_dao.hpp"
#include "base_datos.hpp"
#include "rola_dao.hpp"

/**
 * @class Controlador
 * @brief Clase para el controlador de la base de datos.
 * @details Se encarga de la comunicación entre el modelo y la vista.
 */
class Controlador : public QObject {
  Q_OBJECT
  Q_PROPERTY(QVariantList rolas READ getRolas NOTIFY rolasChanged)

private:

  /* La ruta del directorio a minar. */
  std::filesystem::path ruta;
  /* La base de datos. */
  BaseDeDatos db;
  /* El dao de las rolas. */
  RolaDao rolaDao;
  /* El dao de los albumés. */
  AlbumDao albumDao;
  /* El dao de los artistas. */
  ArtistaDao artistaDao;

  /* Las rolas de la base de datos. */
  QVariantList rolas;

  /* Actualiza las rolas. */
  void actualizaRolas();

public:

  /**
   * @brief El constructor.
   */
  explicit Controlador(std::filesystem::path ruta, QObject* parent = nullptr);

  /**
   * @brief Mina el directorio y muestra los resultados.
   */
  Q_INVOKABLE void minar();

  /**
   * @brief Regresa las rolas de la base de datos.
   */
  QVariantList getRolas() const;

signals:

  /**
   * @brief Notifica que las rolas cambiaron.
   */
  void rolasChanged();
};
