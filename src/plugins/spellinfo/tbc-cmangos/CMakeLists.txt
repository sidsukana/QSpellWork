cmake_minimum_required(VERSION 3.27)

project(tbc-cmangos LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_DEBUG_POSTFIX d)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Sql)

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
    Qt${QT_VERSION_MAJOR}::Sql
    QSW
)

target_compile_definitions(${PROJECT_NAME} PRIVATE UNTITLED_LIBRARY)

install(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION plugins/spellinfo/${PROJECT_NAME} COMPONENT Plugins
    LIBRARY DESTINATION plugins/spellinfo/${PROJECT_NAME} COMPONENT Plugins
)

install(FILES
    template.html
    template.css
    enums.json
    DESTINATION plugins/spellinfo/${PROJECT_NAME}
    COMPONENT Plugins
)
