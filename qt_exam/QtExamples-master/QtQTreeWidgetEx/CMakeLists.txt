cmake_minimum_required(VERSION 3.25)
project(qt_exam)

set(CMAKE_CXX_STANDARD 17)
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
        Network
        Svg
        REQUIRED)
find_package(OpenSSL REQUIRED)
include_directories(${OPENSSL_INCLUDE_DIR})

add_executable(QtQTreeWidgetEx main.cpp ExQTreeWidget.cpp )


target_link_libraries(QtQTreeWidgetEx
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        Qt5::Network
        Qt5::Svg
        )
