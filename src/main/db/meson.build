db_sources = files()

lib_db = static_library(
    'db_core',
    db_sources,
)

executable(
    'musical-db',
    'main.cpp',
    link_with: [lib_db, db_view],
    install: true,
)
