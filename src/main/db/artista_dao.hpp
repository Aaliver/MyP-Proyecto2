/**
 * @file artista_dao.hpp
 * @brief Definición del objeto de acceso a los artistas.
 */
#pragma once

#include <sqlite3.h>
#include <unordered_set>
#include <vector>

#include "artista.hpp"

/**
 * @class ArtistaDao
 * @brief Clase que maneja los artistas de la base de datos.
 * @details Se encarga de realizar las consultas de los artistas.
 */
class ArtistaDao {

private:

  /* La conexión de la base de datos. */
  sqlite3* conexion;

public:

  /**
   * @brief El constructor.
   */
  explicit ArtistaDao(sqlite3* conexion);

  /**
   * @brief Añade artistas a la base de datos.
   * @param artistas el vector con los artistas a añadir.
   */
  void addArtistas(const std::vector<Artista>& artistas);

  /**
   * @brief Regresa un artista de la base de datos.
   * @param id el identificador del artista a regresar.
   * @return un artista de la base de datos.
   */
  Artista getArtista(int id) const;

  /**
   * @brief Actualiza un artista en la base de datos.
   * @param artista el artista a actualizar.
   */
  void updateArtista(const Artista& artista);

  /**
   * @brief Elimina un artista de la base de datos.
   * @param id el identificador del artista a eliminar.
   */
  void deleteArtista(int id);

  /**
   * @brief Regresa un conjunto con los nombres de los artistas de la base de datos.
   * @return un conjunto con los nombres de todas los artistas.
   */
  std::unordered_set<std::string> getArtistasNames() const;
};
