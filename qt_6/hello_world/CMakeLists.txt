cmake_minimum_required(VERSION 3.25)
project(hello_world)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        Qml
        Quick
        REQUIRED)

add_executable(hello_world main.cpp
        src/code/QML_Reloader.cpp
        src/code/QML_Reloader.h)
target_link_libraries(hello_world
        Qt::Core
        Qt::Gui
        Qt::Widgets
        Qt6::Qml
        Qt6::Quick
        )
