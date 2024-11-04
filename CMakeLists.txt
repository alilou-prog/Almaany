cmake_minimum_required(VERSION 3.16)

project(Almaany VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Pass the source directory to the application as a compile-time definition
add_definitions(-DSOURCE_DIR="${CMAKE_SOURCE_DIR}")

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

find_package(Qt6 REQUIRED COMPONENTS Sql)

add_executable(Almaany
    main.cpp
    almaanyapp.h almaanyapp.cpp almaanyapp.ui
)

target_link_libraries(Almaany PRIVATE Qt6::Sql)
target_link_libraries(Almaany PRIVATE Qt6::Widgets)
