#include "controlador.hpp"

#include <unordered_map>
#include <unordered_set>

#include "album.hpp"
#include "artista.hpp"
#include "minero.hpp"
#include "rola.hpp"

Controlador::Controlador(std::filesystem::path ruta, QObject* parent) :
  QObject(parent), ruta(ruta), rolaDao(db.getConexion()),
  albumDao(db.getConexion()), artistaDao(db.getConexion()) {}

void Controlador::minar() {
  std::unordered_set<std::string> rolas = rolaDao.getRolasPath();
  std::unordered_map<std::string, int> albums = albumDao.getAlbumsIds();
  std::unordered_map<std::string, int> artistas = artistaDao.getArtistasIds();
  Elementos elementos = Minero::mina(ruta, rolas, albums, artistas);
  for (const auto& [name, id]: artistaDao.addArtistas(elementos.artistasNuevos))
    artistas[name] = id;
  for (const auto& [path, id]: albumDao.addAlbums(elementos.albumsNuevos))
    albums[path] = id;
  rolaDao.addRolas(elementos.rolasNuevas, artistas, albums);
  actualizaRolas(rolaDao.getRolasView());
}

void Controlador::actualizaRolas(const std::vector<VistaRola>& nuevasRolas) {
    rolas.clear();
    for (const auto& vista: nuevasRolas) {
        QVariantMap fila;
        fila["id_rola"] = vista.rola.getRolaId();
        fila["id_performer"] = vista.rola.getArtistId();
        fila["performer"] = QString::fromStdString(vista.artista);
        fila["id_album"] = vista.rola.getAlbumId();
        fila["album"] = QString::fromStdString(vista.album);
        fila["path"] = QString::fromStdString(vista.rola.getPath());
        fila["title"] = QString::fromStdString(vista.rola.getTitle());
        fila["track"] = vista.rola.getTrack();
        fila["year"] = vista.rola.getYear();
        fila["genre"] = QString::fromStdString(vista.rola.getGenre());
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
  VistaRola vista;
  vista.rola = rola;
  vista.album = datos["album"].toString().toStdString();
  vista.artista = datos["performer"].toString().toStdString();
  rolaDao.updateRola(vista);
  actualizaRolas(rolaDao.getRolasView());
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

void Controlador::eliminaRola(const QVariantMap& datos) {
  rolaDao.deleteRola(datos["id_rola"].toInt());
  actualizaRolas(rolaDao.getRolasView());
}

void Controlador::buscaRolas(const QVariantMap& parametros) {
  ParamRola param;
  if (parametros.contains("title"))
    param.title = parametros["title"].toString().toStdString();
  if (parametros.contains("year"))
    param.year = parametros["year"].toInt();
  if (parametros.contains("genre"))
    param.genre = parametros["genre"].toString().toStdString();
  if (parametros.contains("album"))
    param.album = parametros["album"].toString().toStdString();
  if (parametros.contains("performer"))
    param.artist = parametros["performer"].toString().toStdString();
  actualizaRolas(rolaDao.searchRolas(param));
}

QUrl Controlador::getQUrl(const QString& path) const {
  return QUrl::fromLocalFile(path);
}

QVariantList Controlador::getRolas() const {
  return rolas;
}
