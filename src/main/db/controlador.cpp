#include "controlador.hpp"

Controlador::Controlador(std::filesystem::path ruta, QObject* parent) :
  QObject(parent), ruta(ruta) {}

Q_INVOKABLE void Controlador::minar() {
  
}
