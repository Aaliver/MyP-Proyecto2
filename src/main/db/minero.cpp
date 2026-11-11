#include "minero.hpp"

#include <unordered_set>

#include <fileref.h>
#include <tag.h>

#include "rola.hpp"

namespace fs = std::filesystem;

std::vector<Rola> Minero::mina(std::filesystem::path ruta, RolaDao dao) {
  std::unordered_set<std::string> rolas = dao.getRolasPath();
  std::vector<Rola> rolasNuevas;
  for (const auto& entrada : fs::recursive_directory_iterator(ruta))
    if (entrada.is_regular_file() && entrada.path().extension() == ".mp3") {
      std::string ruta = entrada.path();
      if (rolas.find(ruta) == rolas.end())
	rolasNuevas.push_back(obtenerRola(ruta));
    }
  return rolasNuevas;
}

Rola Minero::obtenerRola(std::string ruta) {
  TagLib::FileRef f(ruta.c_str());
  bool utf8 = true;
  Rola rola;
  //rola.setRolaId(f.tag()->);
  //rola.setArtistId(f.tag()->artist());
  //rola.setAlbumId(f.tag()->album());
  rola.setPath(ruta);
  rola.setTitle(f.tag()->title().to8Bit(utf8));
  rola.setTrack(f.tag()->track());
  rola.setYear(f.tag()->year());
  rola.setGenre(f.tag()->genre().to8Bit(utf8));
  return rola;
}
