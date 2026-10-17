import_qt6 = import('qt6')

view_resources = import_qt6.compile_resources(sources: 'recursos.qrc')

db_view = static_library(
    'view_core', 
    view_resources, 
    dependencies: qt6_dep
)
