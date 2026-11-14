#include "controlador.hpp"

#include "minero.hpp"

Controlador::Controlador(std::filesystem::path ruta, QObject* parent) :
  QObject(parent), ruta(ruta), rolaDao(db.getConexion()),
  albumDao(db.getConexion()), artistaDao(db.getConexion()) {}

Q_INVOKABLE void Controlador::minar() {
  Elementos elementos = Minero::mina(ruta, rolaDao, albumDao, artistaDao);
  artistaDao.addArtistas(elementos.artistasNuevos);
  for (const auto& album: elementos.albumsNuevos)
    albumDao.addAlbum(album);
  for (const auto& rola: elementos.rolasNuevas)
    rolaDao.addRola(rola);
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

QVariantList Controlador::getRolas() const {
    return rolas;
}
