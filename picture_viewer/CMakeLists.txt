cmake_minimum_required(VERSION 3.25)
project(picture_viewer)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# 设置变量PROJECT_ROOT_DIR为项目根目录路径
get_filename_component(PROJECT_ROOT_DIR ${CMAKE_SOURCE_DIR} ABSOLUTE)

# 将PROJECT_ROOT_DIR定义为预处理器宏
add_definitions(-DPROJECT_ROOT_DIR="${PROJECT_ROOT_DIR}")
set(CMAKE_PREFIX_PATH "F:\\QT5_9_9\\5.9.9\\mingw53_32")


find_package(Qt5 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(picture_viewer
        WIN32
        src/main.cpp
        src/function.cpp
        src/function.h
        src/ui/ui_file/Qtree_ui.h
        src/some_function/my_photo_Graphics.cpp
        src/some_function/my_photo_Graphics.h
        src/some_function/my_Qtreewidget.cpp
        src/some_function/my_Qtreewidget.h)


target_link_libraries(picture_viewer
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        )

