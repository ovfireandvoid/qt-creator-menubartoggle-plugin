cmake_minimum_required(VERSION 3.10)

project(qt-creator-menubartoggle-plugin)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)

find_package(QtCreator COMPONENTS Core REQUIRED)
find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)

set(QtX Qt${QT_VERSION_MAJOR})

add_qtc_plugin(MenuBarToggle
    DEPENDS
        ${QtX}::Widgets
        QtCreator::ExtensionSystem
        QtCreator::Utils
    PLUGIN_DEPENDS
        QtCreator::Core
    SOURCES
        src/menubartoggle_constants.h
        src/menubartoggle_plugin.h
        src/menubartoggle_plugin.cpp
        MenuBarToggle.json.in
        README.md
    )
