project(
    'musical-database',
    'cpp',
    default_options: ['cpp_std=c++17', 'warning_level=2'],
)

qt6_dep = dependency('qt6', modules: ['Core', 'Gui', 'Qml', 'Quick'], required: true)

subdir('src/main/view')
subdir('src/main/db')

doxygen = find_program('doxygen', required: false)

if doxygen.found()
    custom_target(
        'docs',
        input: files('Doxyfile'),
        output: 'html',
        command: [doxygen, '@INPUT@'],
        build_by_default: true
    )
endif
