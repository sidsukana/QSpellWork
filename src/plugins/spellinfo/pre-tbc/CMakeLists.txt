cmake_minimum_required(VERSION 3.27)

project(pre-tbc LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_DEBUG_POSTFIX d)

find_package(Qt6 REQUIRED COMPONENTS Core Gui)

add_library(${PROJECT_NAME} SHARED
    spellinfo.h
    spellinfo.cpp
    structure.h
    structure.cpp
    ${PROJECT_NAME}.json
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Gui
    QSW
)

target_compile_definitions(${PROJECT_NAME} PRIVATE UNTITLED_LIBRARY)
