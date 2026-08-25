cmake_minimum_required(VERSION 3.27)

project(wotlk LANGUAGES CXX)

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

if(MSVC)
  # Define OutDir to source/bin/(platform)_(configuaration) folder.
  set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/src/Debug/plugins/spellinfo/${PROJECT_NAME}")
  set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/src/Release/plugins/spellinfo/${PROJECT_NAME}")
  set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO "${CMAKE_BINARY_DIR}/src/RelWithDebugInfo/plugins/spellinfo/${PROJECT_NAME}")
  set_target_properties(${PROJECT_NAME} PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "$(OutDir)")
  set_target_properties(${PROJECT_NAME} PROPERTIES PROJECT_LABEL ${PROJECT_NAME})
  set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "plugins")

  add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different \"${CMAKE_CURRENT_SOURCE_DIR}/enums.json\" \"${CMAKE_BINARY_DIR}/src/Debug/plugins/spellinfo/${PROJECT_NAME}/enums.json\")

  add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different \"${CMAKE_CURRENT_SOURCE_DIR}/template.css\" \"${CMAKE_BINARY_DIR}/src/Debug/plugins/spellinfo/${PROJECT_NAME}/template.css\")

  add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different \"${CMAKE_CURRENT_SOURCE_DIR}/template.html\" \"${CMAKE_BINARY_DIR}/src/Debug/plugins/spellinfo/${PROJECT_NAME}/template.html\")

  add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different \"${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}.json\" \"${CMAKE_BINARY_DIR}/src/Debug/plugins/spellinfo/${PROJECT_NAME}/${PROJECT_NAME}.json\")
endif()

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
