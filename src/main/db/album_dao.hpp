/**
 * @file album_dao.hpp
 * @brief Definición del objeto de acceso a los albums.
 */
#pragma once

#include <sqlite3.h>
#include <unordered_set>

#include "album.hpp"

/**
 * @class AlbumDao
 * @brief Clase que maneja los albums de la base de datos.
 * @details Se encarga de realizar las consultas de los albums.
 */
class AlbumDao {

private:

  /* La conexión de la base de datos. */
  sqlite3* conexion;

public:

  /**
   * @brief El constructor.
   */
  explicit AlbumDao(sqlite3* conexion);

  /**
   * @brief Añade albums a la base de datos.
   * @param albums los albums a añadir.
   */
  void addAlbums(const std::vector<Album>& albums);

  /**
   * @brief Regresa un album de la base de datos.
   * @param id el identificador del album a regresar.
   * @return un album de la base de datos.
   */
  Album getAlbum(int id) const;

  /**
   * @brief Actualiza un album en la base de datos.
   * @param album el album a actualizar.
   */
  void updateAlbum(const Album& album);

  /**
   * @brief Elimina un album de la base de datos.
   * @param id el identificador del album a eliminar.
   */
  void deleteAlbum(int id);

  /**
   * @brief Regresa un conjunto con las rutas de los albums de la base de datos.
   * @return un conjunto con las rutas de todos los albums.
   */
  std::unordered_set<std::string> getAlbumsPath() const;
};
