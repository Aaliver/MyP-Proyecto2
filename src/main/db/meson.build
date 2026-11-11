db_sources = files(
    'aplicacion.cpp',
    'minero.cpp',
    'rola.cpp',
    'rola_dao.cpp',
    'album.cpp',
    'artista.cpp',
    'base_datos.cpp',
)

taglib_dep = dependency('taglib', required: true)

sqlite3_dep = dependency('sqlite3', required: true)

dep = [
    qt6_dep,
    taglib_dep,
    sqlite3_dep,
]

lib_db = static_library(
    'db_core',
    db_sources,
    dependencies: dep,
)

executable(
    'musical-db',
    'main.cpp',
    view_resources,
    link_with: lib_db,
    dependencies: qt6_dep,
    install: true,
)
