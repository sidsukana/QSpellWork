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

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/version.h.in ${CMAKE_CURRENT_SOURCE_DIR}/version.h @ONLY)

qt_add_resources(SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/assets/assets.qrc)

qt_add_executable(${PROJECT_NAME}
    WIN32
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

target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Gui
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Sql
    Qt${QT_VERSION_MAJOR}::Concurrent
    Qt${QT_VERSION_MAJOR}::Qml
    Qt${QT_VERSION_MAJOR}::WebEngineCore
    Qt${QT_VERSION_MAJOR}::WebEngineWidgets
    storm
    qt-mustache
)

add_subdirectory(plugins)

install(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION . COMPONENT Application
    BUNDLE DESTINATION . COMPONENT Application
)

if(WIN32)
    set(TARGET_NAME "QSW")
    set(CONFIGURED_SCRIPT_PATH "${CMAKE_CURRENT_BINARY_DIR}/deploy-qt-windows.cmake")

    configure_file(
        "${CMAKE_SOURCE_DIR}/cmake/deploy-qt-windows.cmake.in"
        "${CONFIGURED_SCRIPT_PATH}"
        @ONLY
    )

    install(SCRIPT "${CONFIGURED_SCRIPT_PATH}"
            COMPONENT Application
    )
endif()
