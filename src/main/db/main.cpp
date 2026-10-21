#include "QGuiApplication"
#include "QQmlApplicationEngine"
#include "aplicacion.hpp"
#include <cstdio>

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

  QQmlApplicationEngine engine;
  const QUrl url(QStringLiteral("qrc:/main.qml"));
  QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
		   &app, [url](QObject *obj, const QUrl &objUrl) {
		     if (!obj && url == objUrl)
		       QCoreApplication::exit(-1);
		   }, Qt::QueuedConnection);
  engine.load(url);

  return app.exec();
}
