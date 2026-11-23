db_sources = files(
    'aplicacion.cpp',
    'minero.cpp',
    'rola.cpp',
    'rola_dao.cpp',
    'album.cpp',
    'album_dao.cpp',
    'artista.cpp',
    'artista_dao.cpp',
    'persona.cpp',
    'persona_dao.cpp',
    'dao_utils.cpp',
    'base_datos.cpp',
    'controlador.cpp',
)

moc_sources = import_qt6.preprocess(
    moc_headers: ['controlador.hpp'],
)

taglib_dep = dependency('taglib', required: true)

sqlite3_dep = dependency('sqlite3', required: true)

lib_db = static_library(
    'db_core',
    db_sources,
    moc_sources,
    dependencies: [qt6_dep, taglib_dep, sqlite3_dep],
)

executable(
    'musical-db',
    'main.cpp',
    view_resources,
    link_with: lib_db,
    dependencies: qt6_dep,
    install: true,
)
