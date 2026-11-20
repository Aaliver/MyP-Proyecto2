#include "minero.hpp"

#include <fileref.h>
#include <tag.h>

#include "album.hpp"
#include "artista.hpp"
#include "rola.hpp"
#include "rola_nueva.hpp"

namespace fs = std::filesystem;

namespace {
  constexpr bool utf8 = true;

  Rola nuevaRola(TagLib::FileRef& file, std::string& ruta) {
    Rola rola;
    rola.setPath(ruta);
    rola.setTitle(file.tag()->title().to8Bit(utf8));
    rola.setTrack(file.tag()->track());
    rola.setYear(file.tag()->year());
    rola.setGenre(file.tag()->genre().to8Bit(utf8));
    return rola;
  }

  Album nuevoAlbum(TagLib::FileRef& file, std::string& directorio) {
    Album album;
    album.setPath(directorio);
    album.setName(file.tag()->album().to8Bit(utf8));
    album.setYear(file.tag()->year());
    return album;
  }

  Artista nuevoArtista(std::string& name) {
    Artista artista;
    int unknown = 2;
    artista.setIdType(unknown);
    artista.setName(name);
    return artista;
  }

  void nuevoElemento(std::string ruta, std::string directorio, Elementos& elementos,
		     std::unordered_map<std::string, int>& albums,
		     std::unordered_map<std::string, int>& artistas) {
    TagLib::FileRef file(ruta.c_str());
    if (file.isNull() || file.tag() == nullptr)
      return;
    RolaNueva nueva;
    if (albums.insert({directorio, -1}).second) {
      Album album = nuevoAlbum(file, directorio);
      nueva.albumPath = directorio;
      elementos.albumsNuevos.push_back(album);
    }
    std::string artistName = file.tag()->artist().to8Bit(utf8);
    if (artistas.insert({artistName, -1}).second) {
      nueva.performerName = artistName;
      elementos.artistasNuevos.push_back(nuevoArtista(artistName));
    }
    nueva.rola = nuevaRola(file, ruta);
    elementos.rolasNuevas.push_back(nueva);
  }
}

Elementos Minero::mina(std::filesystem::path ruta,
		       std::unordered_set<std::string>& rolas,
		       std::unordered_map<std::string, int>& albums,
		       std::unordered_map<std::string, int>& artistas) {
  Elementos elementos;

  try {
    for (const auto& entrada : fs::recursive_directory_iterator(ruta, fs::directory_options::skip_permission_denied))
      if (entrada.is_regular_file() && entrada.path().extension() == ".mp3") {
	std::string ruta = entrada.path().string();
	std::string directorio = entrada.path().parent_path().string();
	if (rolas.find(ruta) == rolas.end())
	  nuevoElemento(ruta, directorio, elementos, albums, artistas);
      }
  } catch (const std::filesystem::filesystem_error& fse) {}

  return elementos;
}
