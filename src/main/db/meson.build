db_sources = files('aplicacion.cpp', 'minero.cpp')

lib_db = static_library(
    'db_core',
    db_sources,
    dependencies: qt6_dep
)

executable(
    'musical-db',
    'main.cpp',
    view_resources,
    link_with: lib_db,
    dependencies: qt6_dep,
    install: true
)
