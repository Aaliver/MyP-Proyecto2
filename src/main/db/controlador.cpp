#include "controlador.hpp"

#include <QUrl>

#include "minero.hpp"

Controlador::Controlador(std::filesystem::path ruta, QObject* parent) :
  QObject(parent), ruta(ruta), rolaDao(db.getConexion()),
  albumDao(db.getConexion()), artistaDao(db.getConexion()) {}

Q_INVOKABLE void Controlador::minar() {
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
        fila["path"] = QUrl::fromLocalFile(QString::fromStdString(rola.getPath()));
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
