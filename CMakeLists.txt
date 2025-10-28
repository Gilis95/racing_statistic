cmake_minimum_required(VERSION 3.24 FATAL_ERROR)
cmake_policy(VERSION 3.24)

project(noobsters VERSION 1.0.0 LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE debug)
set(CMAKE_COMPILE_WARNING_AS_ERROR OFF)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++23")


if (${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
    add_definitions(-DNOOBSTERS_LINUX=1)
endif ()

if ("${CMAKE_SYSTEM_NAME}" STREQUAL "Windows")
    add_definitions(-DNOOBSTERS_WINDOWS=1)
endif ()

#Fetch common dependencies
#include(cmake/FetchDependencies.cmake)

#Submodules
#add_subdirectory(noobsters-domain)
#add_subdirectory(noobsters-networking)
#add_subdirectory(noobsters-i18n)
add_subdirectory(noobsters-ui)

#add_library(wunder::wunder-renderer ALIAS wunder-renderer)
#add_executable(wunder::wunder-sandbox ALIAS wunder-sandbox)
