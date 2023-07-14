
cmake_minimum_required(VERSION 3.25)

project(boll)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_AUTOMOC ON)


# 设置Qt路径
set(CMAKE_PREFIX_PATH "F:/QT5_9_9/5.9.9/mingw53_32")

# 查找Qt的组件
find_package(Qt5 COMPONENTS
        Multimedia
        MultimediaWidgets
        Core
        Gui
        Widgets
        Network
        Svg
        REQUIRED)

# 编译源代码
add_executable(boll
        main.cpp
        src/Collision.h
        src/Collision.cpp
        src/Object_category.h
        src/Object_category.cpp
        )
# 链接Qt库
target_link_libraries(boll
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        Qt5::Network
        Qt5::Svg
        Qt5::Multimedia
        Qt5::MultimediaWidgets
        )

