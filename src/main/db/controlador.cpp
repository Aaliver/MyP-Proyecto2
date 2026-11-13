#include "controlador.hpp"

#include "minero.hpp"

Controlador::Controlador(std::filesystem::path ruta, QObject* parent) :
  QObject(parent), ruta(ruta), rolaDao(db.getConexion()),
  albumDao(db.getConexion()), artistaDao(db.getConexion()) {}

Q_INVOKABLE void Controlador::minar() {
  Elementos elementos = Minero::mina(ruta, rolaDao, albumDao, artistaDao);
  for (const auto& artista: elementos.artistasNuevos)
    artistaDao.addArtista(artista);
  for (const auto& album: elementos.albumsNuevos)
    albumDao.addAlbum(album);
  for (const auto& rola: elementos.rolasNuevas)
    rolaDao.addRola(rola);
}
