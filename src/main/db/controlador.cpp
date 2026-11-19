#include "controlador.hpp"

#include "album.hpp"
#include "artista.hpp"
#include "minero.hpp"
#include "rola.hpp"

Controlador::Controlador(std::filesystem::path ruta, QObject* parent) :
  QObject(parent), ruta(ruta), rolaDao(db.getConexion()),
  albumDao(db.getConexion()), artistaDao(db.getConexion()) {}

void Controlador::minar() {
  Elementos elementos = Minero::mina(ruta, rolaDao, albumDao, artistaDao);
  artistaDao.addArtistas(elementos.artistasNuevos);
  albumDao.addAlbums(elementos.albumsNuevos);
  rolaDao.addRolas(elementos.rolasNuevas);
  actualizaRolas();
}

void Controlador::actualizaRolas() {
    rolas.clear();
    for (const auto& rola: rolaDao.getRolas()) {
        QVariantMap fila;
        fila["id_rola"] = rola.getRolaId();
        fila["id_performer"] = rola.getArtistId();
        fila["id_album"] = rola.getAlbumId();
        fila["path"] = QString::fromStdString(rola.getPath());
        fila["title"] = QString::fromStdString(rola.getTitle());
        fila["track"] = rola.getTrack();
        fila["year"] = rola.getYear();
        fila["genre"] = QString::fromStdString(rola.getGenre());
        rolas.append(fila);
    }
    emit rolasChanged();
}

void Controlador::actualizaRola(const QVariantMap& datos) {
  Rola rola;
  rola.setRolaId(datos["id_rola"].toInt());
  rola.setArtistId(datos["id_performer"].toInt());
  rola.setAlbumId(datos["id_album"].toInt());
  rola.setPath(datos["path"].toString().toStdString());
  rola.setTitle(datos["title"].toString().toStdString());
  rola.setTrack(datos["track"].toInt());
  rola.setYear(datos["year"].toInt());
  rola.setGenre(datos["genre"].toString().toStdString());
  rolaDao.updateRola(rola);
  actualizaRolas();
}

void Controlador::actualizaAlbum(const QVariantMap& datos) {
  Album album;
  album.setId(datos["id_album"].toInt());
  album.setPath(datos["path"].toString().toStdString());
  album.setName(datos["name"].toString().toStdString());
  album.setYear(datos["year"].toInt());
  albumDao.updateAlbum(album);
}

void Controlador::actualizaArtista(const QVariantMap& datos) {
  Artista artista;
  artista.setId(datos["id_performer"].toInt());
  artista.setIdType(datos["id_type"].toInt());
  artista.setName(datos["name"].toString().toStdString());
  artistaDao.updateArtista(artista);
}

QUrl Controlador::getQUrl(const QString& path) const {
  return QUrl::fromLocalFile(path);
}

QVariantList Controlador::getRolas() const {
  return rolas;
}
