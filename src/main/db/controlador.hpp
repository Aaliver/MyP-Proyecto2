/**
 * @file controlador.hpp
 * @brief Definición del controlador.
 */
#pragma once

#include <filesystem>

#include <QObject>
#include <QUrl>
#include <QVariantList>
#include <QVariantMap>

#include "album_dao.hpp"
#include "artista_dao.hpp"
#include "base_datos.hpp"
#include "persona_dao.hpp"
#include "rola_dao.hpp"
#include "vista_rola.hpp"

/**
 * @class Controlador
 * @brief Clase para el controlador de la base de datos.
 * @details Se encarga de la comunicación entre el modelo y la vista.
 */
class Controlador : public QObject {
  Q_OBJECT
  /**
   * @brief Las rolas de la base de datos.
   * Emite rolasChanged() cuando se modifican.
   */
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
  /* El dao de las personas. */
  PersonaDao personaDao;

  /* Las rolas de la base de datos. */
  QVariantList rolas;

  /* Actualiza las rolas. */
  void actualizaRolas(const std::vector<VistaRola>& nuevasRolas);

public:

  /**
   * @brief El constructor.
   * @param ruta la ruta del directorio donde obtener los datos de la base de datos.
   * @param parent el objeto padre.
   */
  explicit Controlador(std::filesystem::path ruta, QObject* parent = nullptr);

  /**
   * @brief Mina el directorio.
   */
  Q_INVOKABLE void minar();

  /**
   * @brief Actualiza una rola en la base de datos.
   * @param datos los datos de la rola a actualizar.
   */
  Q_INVOKABLE void actualizaRola(const QVariantMap& datos);

  /**
   * @brief Actualiza un album en la base de datos.
   * @param datos los datos del album a actualizar.
   */
  Q_INVOKABLE void actualizaAlbum(const QVariantMap& datos);

  /**
   * @brief Actualiza un artista en la base de datos.
   * @param datos los datos del artista a actualizar.
   */
  Q_INVOKABLE void actualizaArtista(const QVariantMap& datos);

  /**
   * @brief Añade una persona a la base de datos.
   * @param datos los datos de la persona a agregar.
   */
  Q_INVOKABLE void agregaPersona(const QVariantMap& datos);

  /**
   * @brief Elimina una rola de la base de datos.
   * @param datos los datos de la rola a eliminar.
   */
  Q_INVOKABLE void eliminaRola(const QVariantMap& datos);

  /**
   * @brief Busca las rolas que cumplen ciertos criterios.
   * @param parametros los criterios que deben cumplir las rolas a buscar.
   */
  Q_INVOKABLE void buscaRolas(const QVariantMap& parametros);

  /**
   * @brief Regresa la QUrl de una ruta.
   * @param path la ruta de la que obtener la QUrl.
   * @return la QUrl de una ruta.
   */
  Q_INVOKABLE QUrl getQUrl(const QString& path) const;

  /**
   * @brief Regresa las rolas de la base de datos.
   * @return las rolas de la base de datos.
   */
  QVariantList getRolas() const;

signals:

  /**
   * @brief Notifica que las rolas cambiaron.
   */
  void rolasChanged();
};
