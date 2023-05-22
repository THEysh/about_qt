
cmake_minimum_required(VERSION 3.25)

project(qt_test)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# 设置Qt路径
set(CMAKE_PREFIX_PATH "F:/QT5_9_9/5.9.9/mingw53_32")

# 查找Qt的组件
find_package(Qt5 COMPONENTS
        Core
        Gui
        Widgets
        Network
        Svg
        REQUIRED)

# 编译源代码
add_executable(qt_test
        main.cpp
        A.cpp
        A.h
        B.cpp
        B.h
        )
# 链接Qt库
target_link_libraries(qt_test
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        Qt5::Network
        Qt5::Svg
        )

