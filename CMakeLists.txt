cmake_minimum_required (VERSION 3.0)
project(kekcat)
include(CMakePackageConfigHelpers)
include(GNUInstallDirs)

#Set OS
if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    add_definitions(-DKEK_OS_LINUX)
    set(KEK_OS_LINUX true)

elseif(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    add_definitions(-DKEK_OS_WINDOWS)
    set(KEK_OS_WINDOWS true)

elseif(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    add_definitions(-DKEK_OS_MACOS)
    set(KEK_OS_MACOS true)

elseif(${CMAKE_SYSTEM_NAME} MATCHES "FreeBSD")
    add_definitions(-DKEK_OS_BSD)
    set(KEK_OS_BSD true)
endif()

option(BUILD_SHARED_LIBS "Build using shared libraries" ON)


add_subdirectory(src)