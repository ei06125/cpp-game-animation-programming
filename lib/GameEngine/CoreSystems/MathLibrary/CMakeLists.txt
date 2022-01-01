# =============================================================================
if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)

  cmake_minimum_required(VERSION 3.21)
  project(MathLibraryProject)

  if(POLICY CMP0077)
    cmake_policy(SET CMP0077 NEW)
  endif()

  if(POLICY CMP0128)
    cmake_policy(SET CMP0128 NEW)
  endif()

  if(NOT MSVC)
    include(GNUInstallDirs)
  else()
    set(CMAKE_INSTALL_PREFIX "C:/dev/AnimationProject")
  endif()

  include(CMakePackageConfigHelpers)
endif()

# =============================================================================
# create library
add_library(MathLibrary SHARED)

# add sources
file(GLOB_RECURSE MathLibrary_SOURCES "*.cpp")
file(GLOB_RECURSE MathLibrary_HEADERS "*.[h|hpp]")
message(DEBUG "MathLibrary_SOURCES: ${MathLibrary_SOURCES}")
message(DEBUG "MathLibrary_HEADERS: ${MathLibrary_HEADERS}")
target_sources(MathLibrary PRIVATE ${MathLibrary_SOURCES})

# create a module definition (.def) file with all global symbols found in the
# input .obj files for a SHARED library
set_target_properties(MathLibrary PROPERTIES WINDOWS_EXPORT_ALL_SYMBOLS ON)

add_library(GameEngine::CoreSystems::MathLibrary ALIAS MathLibrary)

# =============================================================================
# add include directories
target_include_directories(
  MathLibrary PUBLIC "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>"
                     $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

# =============================================================================
# install the target and create export-set
if(NOT MSVC)
  install(
    TARGETS MathLibrary
    EXPORT MathLibraryTargets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    INCLUDES
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
  )
else()
  install(
    TARGETS MathLibrary
    EXPORT MathLibraryTargets
    LIBRARY DESTINATION GameEngine/CoreSystems/MathLibrary
    ARCHIVE DESTINATION GameEngine/CoreSystems/MathLibrary
    RUNTIME DESTINATION GameEngine/CoreSystems/MathLibrary
    INCLUDES
    DESTINATION GameEngine/CoreSystems/MathLibrary
  )
endif()

# =============================================================================
# install header files
if(NOT MSVC)
  install(FILES ${MathLibrary_HEADERS} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
else()
  install(FILES ${MathLibrary_HEADERS}
          DESTINATION GameEngine/CoreSystems/MathLibrary
  )
endif()

# =============================================================================
# generate and install export file
if(NOT MSVC)
  install(
    EXPORT MathLibraryTargets
    FILE MathLibraryTargets.cmake
    NAMESPACE GameEngine::CoreSystems::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/GameEngine/CoreSystems
  )
else()
  install(
    EXPORT MathLibraryTargets
    FILE MathLibraryTargets.cmake
    NAMESPACE GameEngine::CoreSystems::
    DESTINATION GameEngine/CoreSystems/MathLibrary
  )
endif()

# =============================================================================
# generate the version file for the config file
write_basic_package_version_file(
  "${CMAKE_CURRENT_BINARY_DIR}/MathLibraryConfigVersion.cmake"
  VERSION "1.0.0"
  COMPATIBILITY AnyNewerVersion
)

# =============================================================================
# create config file
if(NOT MSVC)
  configure_package_config_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/Config.cmake.in
    "${CMAKE_CURRENT_BINARY_DIR}/MathLibraryConfig.cmake"
    INSTALL_DESTINATION
    ${CMAKE_INSTALL_DATAROOTDIR}/cmake/MathLibrary
    NO_CHECK_REQUIRED_COMPONENTS_MACRO
  )
else()
  configure_package_config_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/Config.cmake.in
    "${CMAKE_CURRENT_BINARY_DIR}/MathLibraryConfig.cmake" INSTALL_DESTINATION
    GameEngine/CoreSystems/MathLibrary NO_CHECK_REQUIRED_COMPONENTS_MACRO
  )
endif()
# =============================================================================
# install config files
if(NOT MSVC)
  install(FILES "${CMAKE_CURRENT_BINARY_DIR}/MathLibraryConfig.cmake"
                "${CMAKE_CURRENT_BINARY_DIR}/MathLibraryConfigVersion.cmake"
          DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/cmake/MathLibrary
  )
else()
  install(FILES "${CMAKE_CURRENT_BINARY_DIR}/MathLibraryConfig.cmake"
                "${CMAKE_CURRENT_BINARY_DIR}/MathLibraryConfigVersion.cmake"
          DESTINATION GameEngine/CoreSystems/MathLibrary
  )
endif()
