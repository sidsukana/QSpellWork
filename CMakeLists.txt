cmake_minimum_required(VERSION 3.27)

project(QSpellWork VERSION 2.5.0 LANGUAGES CXX)

set(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR}/install CACHE PATH "Install directory" FORCE)

option(QSW_PACKAGE "Run CPack after build" OFF)

add_subdirectory(dep)
add_subdirectory(src)

if (QSW_PACKAGE)
    set(CPACK_GENERATOR "IFW")
    set(CPACK_STRIP_FILES TRUE)
    set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "QSpellWork is a spell viewer for World of Warcraft")
    set(CPACK_IFW_PACKAGE_TITLE "QSpellWork")
    set(CPACK_IFW_PACKAGE_START_MENU_DIRECTORY "QSpellWork")
    set(CPACK_IFW_TARGET_DIRECTORY "@HomeDir@/QSpellWork")
    set(CPACK_IFW_PACKAGE_ALLOW_NON_ASCII_CHARACTERS ON)
    set(CPACK_IFW_PACKAGE_VERSION ${CMAKE_PROJECT_VERSION})
    set(CPACK_COMPONENTS_GROUPING ALL_COMPONENTS_IN_ONE)

    set(CPACK_COMPONENTS_ALL Application Plugins)

    include(CPack)
    include(CPackIFW)

    if(${CPACK_IFW_BINARYCREATOR_EXECUTABLE} MATCHES "NOTFOUND")
        message(SEND_ERROR "Could not detect QtIFW tools. Set the CPACK_IFW_ROOT variable manualy." )
    endif()
endif()
