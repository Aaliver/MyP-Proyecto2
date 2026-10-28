#include "minero.hpp"

namespace fs = std::filesystem;

std::vector<std::string> Minero::mina(std::filesystem::path ruta) {
  std::vector<std::string> rutas;
  for (const auto& entrada : fs::recursive_directory_iterator(ruta))
    if (entrada.is_regular_file() && entrada.path().extension() == ".mp3")
      rutas.push_back(entrada.path().string());
  return rutas;
}
