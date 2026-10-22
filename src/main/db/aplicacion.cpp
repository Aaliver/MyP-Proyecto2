#include "aplicacion.hpp"

#include <QCoreApplication>
#include <QGuiApplication>

namespace fs = std::filesystem;

Aplicacion::Aplicacion(int argc, char* argv[]) {
  valida(argc, argv);
}

void Aplicacion::valida(int argc, char* argv[]) {
  if (argc != 2)
    throw std::invalid_argument("Cantidad incorrecta de argumentos.");
  validaRuta(std::string(argv[1]));
}

void Aplicacion::validaRuta(std::string ruta) {
  fs::path dir(ruta);
  if (!fs::exists(dir))
    throw std::invalid_argument("El directorio de entrada no existe.");
  if (!fs::is_directory(dir))
    throw std::invalid_argument("La entrada no es un directorio.");
  this->ruta = dir;
}

int Aplicacion::ejecuta() {
  const QUrl url(QStringLiteral("qrc:/Main.qml"));
  QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
		   qApp, [url](QObject *obj, const QUrl &objUrl) {
		     if (!obj && url == objUrl)
		       QCoreApplication::exit(-1);
		   }, Qt::QueuedConnection);
  engine.load(url);
  return qApp->exec();
}
