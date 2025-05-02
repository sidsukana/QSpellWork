cmake_minimum_required(VERSION 3.27)

project(QSW)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_UNITY_BUILD OFF)
set(UNITY_BUILD_BATCH_SIZE 8)
set(UNITY_BUILD_MODE GROUP)
set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR}/install CACHE PATH "" FORCE)

find_package(Qt6 6.8 COMPONENTS Core Gui Widgets Sql Concurrent Qml WebEngineCore WebEngineWidgets REQUIRED)
qt_standard_project_setup(REQUIRES 6.8)

include_directories(${PROJECT_NAME} PUBLIC
    ${PROJECT_SOURCE_DIR}
)

file(GLOB SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
    *.cpp
)

file(GLOB HEADERS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
    *.h
)

file(GLOB UI_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
    *.ui
)

qt_add_resources(SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/assets/assets.qrc)

qt_add_executable(${PROJECT_NAME}
    MANUAL_FINALIZATION
        ${SOURCES}
        ${HEADERS}
        ${CMAKE_CURRENT_SOURCE_DIR}/assets/appicon.rc
)

add_definitions(-DQSW_LIB)
set_property(TARGET ${PROJECT_NAME} PROPERTY ENABLE_EXPORTS 1)

qt_add_ui(${PROJECT_NAME}
    SOURCES
        ${UI_FILES}
)

target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Core Qt6::Gui Qt6::Widgets Qt6::Sql Qt6::Concurrent Qt6::Qml Qt6::WebEngineCore Qt6::WebEngineWidgets storm qt-mustache)

add_subdirectory(plugins)
