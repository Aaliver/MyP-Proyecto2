#include <cstdio>

#include <QGuiApplication>

#include "aplicacion.hpp"

int error(const char* mensaje) {
  std::fprintf(stderr, "%s\n", mensaje);
  return 1;
}

int main(int argc, char* argv[]) {
  QGuiApplication app(argc, argv);

  try {
    Aplicacion aplicacion(argc, argv);
    return aplicacion.ejecuta();
  } catch (const std::invalid_argument& ia) {
    return error(ia.what());
  }
}
