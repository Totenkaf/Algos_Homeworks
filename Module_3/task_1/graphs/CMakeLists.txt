# Copyright 2022 by Artem Ustsov

# ==============================================================================
# I | General project settings
# ==============================================================================
cmake_minimum_required(VERSION 3.14)
project(graphs)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -Wall -Wextra -Wpedantic -Werror")

# ==============================================================================
# II | Preinstall settings
# ==============================================================================

# ------------------------------------------------------------------------------
# 1 | Include subdirectories
# ------------------------------------------------------------------------------

set(${PROJECT_NAME}_lib_includes ${PROJECT_SOURCE_DIR}/include)
message("INCLUDES_DIR = ${${PROJECT_NAME}_lib_includes}")
include(ExternalProject)

set(${PROJECT_NAME}_lib_sources ${PROJECT_SOURCE_DIR}/src)
message("SOURCE_DIR = ${${PROJECT_NAME}_lib_sources}")


# ------------------------------------------------------------------------------
# 2 | Main executables
# ------------------------------------------------------------------------------
set(GRAPHS_LIB_FILES ${${PROJECT_NAME}_lib_sources}/IGraph.cpp
                     ${${PROJECT_NAME}_lib_sources}/ListGraph.cpp
                     ${${PROJECT_NAME}_lib_sources}/MatrixGraph.cpp
                     ${${PROJECT_NAME}_lib_sources}/SetGraph.cpp
                     ${${PROJECT_NAME}_lib_sources}/ArcGraph.cpp
   )

add_library(graphs_lib SHARED ${GRAPHS_LIB_FILES})
target_include_directories(graphs_lib PUBLIC ${${PROJECT_NAME}_lib_includes})

# ==============================================================================
# III | Tests
# ==============================================================================

# ------------------------------------------------------------------------------
# 1 | Unit tests
# ------------------------------------------------------------------------------
option(BUILD_TESTS "Build all tests." OFF) # Makes boolean 'unit_test' available.

if(BUILD_TESTS)
  add_subdirectory(test)
endif()