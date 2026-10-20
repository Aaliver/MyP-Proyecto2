db_sources = files('scanner.cpp')

lib_db = static_library(
    'db_core',
    db_sources,
)

executable(
    'musical-db',
    'main.cpp',
    view_resources,
    link_with: lib_db,
    dependencies: qt6_dep,
    install: true
)
