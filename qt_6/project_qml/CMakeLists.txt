cmake_minimum_required(VERSION 3.25)
project(project_qml)

if (NOT Qt6_FOUND)
    set(CMAKE_PREFIX_PATH "F:/QT6/6.2.4/mingw_64")
endif()

set(CMAKE_CXX_STANDARD 20)
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

add_executable(project_qml main.cpp)
target_link_libraries(project_qml
        Qt::Core
        Qt::Gui
        Qt::Widgets
        Qt6::Qml
        Qt6::Quick
        )

