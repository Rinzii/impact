cmake_minimum_required(VERSION 3.26)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_DEBUG_POSTFIX "-d")

if (NOT DEFINED IMPACT_ROOT_DIR)
    set(IMPACT_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})
endif()


set(impact_version 0.1.0)

project(impact VERSION ${impact_version} LANGUAGES CXX)

include(${IMPACT_ROOT_DIR}/cmake/func/AddTargetSource.cmake)

# Option to enable building the editor
option(BUILD_IMPACT_EDITOR "Build ImpactEditor (C# project)" OFF)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

# Include ImpactEngine & external dependencies
add_subdirectory(external)
add_subdirectory(ImpactEngine)
