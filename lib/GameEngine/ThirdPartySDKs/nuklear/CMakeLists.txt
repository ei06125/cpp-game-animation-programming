# =============================================================================
if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
  cmake_minimum_required(VERSION 3.21)
  project(nuklear)
  if(POLICY CMP0077)
    cmake_policy(SET CMP0077 NEW)
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
add_library(nuklear SHARED nuklear.c)

set(glad_DIR "${CMAKE_INSTALL_PREFIX}/GameEngine/ThirdPartySDKs/glad")
find_package(glad 1.0)

target_link_libraries(nuklear PRIVATE GameEngine::ThirdPartySDKs::glad)

# create a module definition (.def) file with all global symbols found in the
# input .obj files for a SHARED library
set_target_properties(nuklear PROPERTIES WINDOWS_EXPORT_ALL_SYMBOLS ON)

target_compile_definitions(nuklear PRIVATE GLAD_GLAPI_EXPORT)

add_library(GameEngine::ThirdPartySDKs::nuklear ALIAS nuklear)

# =============================================================================
# add include directories
target_include_directories(
  nuklear PUBLIC "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>"
                 $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

# =============================================================================
# install the target and create export-set
if(NOT MSVC)
  install(
    TARGETS nuklear
    EXPORT nuklearTargets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}/GameEngine/ThirdPartySDKs
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}/GameEngine/ThirdPartySDKs
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}/GameEngine/ThirdPartySDKs
    INCLUDES
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/GameEngine/ThirdPartySDKs
  )
else()
  install(
    TARGETS nuklear
    EXPORT nuklearTargets
    LIBRARY DESTINATION GameEngine/ThirdPartySDKs/nuklear
    ARCHIVE DESTINATION GameEngine/ThirdPartySDKs/nuklear
    RUNTIME DESTINATION GameEngine/ThirdPartySDKs/nuklear
    INCLUDES
    DESTINATION GameEngine/ThirdPartySDKs/nuklear
  )
endif()

# =============================================================================
# install header file
if(NOT MSVC)
  install(FILES nuklear.h
          DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/GameEngine/ThirdPartySDKs/
  )
else()
  install(FILES nuklear.h DESTINATION GameEngine/ThirdPartySDKs/nuklear/)
endif()

# =============================================================================
# generate and install export file
if(NOT MSVC)
  install(
    EXPORT nuklearTargets
    FILE nuklearTargets.cmake
    NAMESPACE GameEngine::ThirdPartySDKs::
    DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/cmake/GameEngine/ThirdPartySDKs
  )
else()
  install(
    EXPORT nuklearTargets
    FILE nuklearTargets.cmake
    NAMESPACE GameEngine::ThirdPartySDKs::
    DESTINATION GameEngine/ThirdPartySDKs/nuklear
  )
endif()

# =============================================================================
# generate the version file for the config file
write_basic_package_version_file(
  "${CMAKE_CURRENT_BINARY_DIR}/nuklearConfigVersion.cmake"
  VERSION "1.0.0"
  COMPATIBILITY AnyNewerVersion
)

# =============================================================================
# create config file
if(NOT MSVC)
  configure_package_config_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/Config.cmake.in
    "${CMAKE_CURRENT_BINARY_DIR}/nuklearConfig.cmake"
    INSTALL_DESTINATION
    ${CMAKE_INSTALL_DATAROOTDIR}/cmake/nuklear
    NO_CHECK_REQUIRED_COMPONENTS_MACRO
  )
else()
  configure_package_config_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/Config.cmake.in
    "${CMAKE_CURRENT_BINARY_DIR}/nuklearConfig.cmake" INSTALL_DESTINATION
    GameEngine/ThirdPartySDKs/nuklear NO_CHECK_REQUIRED_COMPONENTS_MACRO
  )
endif()

# =============================================================================
# install config files
if(NOT MSVC)
  install(FILES "${CMAKE_CURRENT_BINARY_DIR}/nuklearConfig.cmake"
                "${CMAKE_CURRENT_BINARY_DIR}/nuklearConfigVersion.cmake"
          DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/cmake/nuklear
  )
else()
  install(FILES "${CMAKE_CURRENT_BINARY_DIR}/nuklearConfig.cmake"
                "${CMAKE_CURRENT_BINARY_DIR}/nuklearConfigVersion.cmake"
          DESTINATION GameEngine/ThirdPartySDKs/nuklear
  )
endif()
