cmake_minimum_required(VERSION 3.21)
project(AnimationProject)

# =============================================================================
# Modules

# include(GenerateExportHeader) include(CMakePrintHelpers)

include(GNUInstallDirs) # make cache variables for install destinations
include(CMakePackageConfigHelpers) # include CMakePackageConfigHelpers macro

# =============================================================================
# Global Settings

# Suppresses the creation of ZERO_CHECK in Visual Studio
set(CMAKE_SUPPRESS_REGENERATION true)
set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_DEBUG_POSTFIX d)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_EXTENSIONS OFF)

set(ROOT_DIR ${CMAKE_CURRENT_LIST_DIR})

if(APPLE)
  set(CMAKE_INSTALL_RPATH "@executable_path/../lib")
elseif(UNIX)
  set(CMAKE_INSTALL_RPATH "$ORIGIN/../lib")
endif()

# control where the static and shared libraries are built so that on windows we
# don't need to tinker with the path to run the executable
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}")

# =============================================================================
# Global Options
option(BUILD_SHARED_LIBS "Build using shared libraries" ON)

# =============================================================================
# Global Properties
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# =============================================================================
add_subdirectory(lib)
add_subdirectory(examples)
