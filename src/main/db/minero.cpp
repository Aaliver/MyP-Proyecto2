#include "minero.hpp"

#include <fileref.h>
#include <tag.h>

#include "album.hpp"
#include "artista.hpp"
#include "rola.hpp"

namespace fs = std::filesystem;

namespace {
  constexpr bool utf8 = true;

  void nuevaRola(TagLib::FileRef& file, std::string& ruta, std::vector<Rola>& rolas) {
    Rola rola;
    rola.setPath(ruta);
    rola.setTitle(file.tag()->title().to8Bit(utf8));
    rola.setTrack(file.tag()->track());
    rola.setYear(file.tag()->year());
    rola.setGenre(file.tag()->genre().to8Bit(utf8));
    rolas.push_back(rola);
  }

  void nuevoAlbum(TagLib::FileRef& file, std::string& directorio,
		  std::vector<Album>& albums) {
    Album album;
    album.setPath(directorio);
    album.setName(file.tag()->album().to8Bit(utf8));
    album.setYear(file.tag()->year());
    albums.push_back(album);
  }

  void nuevoArtista(std::string& name, std::vector<Artista>& artistas) {
    Artista artista;
    artista.setIdType(2);
    artista.setName(name);
    artistas.push_back(artista);
  }

  void nuevoElemento(std::string ruta, std::string directorio, Elementos& elementos,
		     std::unordered_map<std::string, int>& albums,
		     std::unordered_set<std::string>& artistas) {
    TagLib::FileRef file(ruta.c_str());
    if (file.isNull() || file.tag() == nullptr)
      return;
    nuevaRola(file, ruta, elementos.rolasNuevas);
    if (albums.insert({directorio, -1}).second)
      nuevoAlbum(file, directorio, elementos.albumsNuevos);
    std::string artistName = file.tag()->artist().to8Bit(utf8);
    if (artistas.insert(artistName).second)
      nuevoArtista(artistName, elementos.artistasNuevos);
  }
}

Elementos Minero::mina(std::filesystem::path ruta,
		       std::unordered_set<std::string>& rolas,
		       std::unordered_map<std::string, int>& albums,
		       std::unordered_set<std::string>& artistas) {
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
