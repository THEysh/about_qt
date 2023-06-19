cmake_minimum_required(VERSION 3.25)
project(qml_fitst_projiect)


set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_PREFIX_PATH "F:/QT6/6.2.4/mingw_64/bin")

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        Qml
        Quick
        REQUIRED)

add_executable(qml_fitst_projiect
        main.cpp
        src/QML_Reloader.h
        src/QML_Reloader.cpp)
target_link_libraries(qml_fitst_projiect
        Qt6::Core
        Qt6::Gui
        Qt6::Widgets
        Qt6::Qml
        Qt6::Quick
        )

