# =============================================================================
if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
  cmake_minimum_required(VERSION 3.21)
  if(POLICY CMP0077)
    cmake_policy(SET CMP0077 NEW)
  endif()
  project(glad)
  if(NOT MSVC)
    include(GNUInstallDirs)
  else()
    set(CMAKE_INSTALL_PREFIX "C:/dev/AnimationProject")
  endif()
  include(CMakePackageConfigHelpers)
endif()

# =============================================================================
# create library
add_library(glad SHARED glad.c)

add_library(GameEngine::ThirdPartySDKs::glad ALIAS glad)

set_target_properties(glad PROPERTIES WINDOWS_EXPORT_ALL_SYMBOLS ON)

target_compile_definitions(
  glad PRIVATE GLAD_GLAPI_EXPORT GLAD_GLAPI_EXPORT_BUILD
)

# =============================================================================
# add include directories
target_include_directories(
  glad PUBLIC "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>"
              $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

# =============================================================================
# install the target and create export-set
if(NOT MSVC)
  install(
    TARGETS glad
    EXPORT GladTargets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}/GameEngine/ThirdPartySDKs
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}/GameEngine/ThirdPartySDKs
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}/GameEngine/ThirdPartySDKs
    INCLUDES
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/GameEngine/ThirdPartySDKs
  )
else()
  install(
    TARGETS glad
    EXPORT GladTargets
    LIBRARY DESTINATION GameEngine/ThirdPartySDKs/glad
    ARCHIVE DESTINATION GameEngine/ThirdPartySDKs/glad
    RUNTIME DESTINATION GameEngine/ThirdPartySDKs/glad
    INCLUDES
    DESTINATION GameEngine/ThirdPartySDKs/glad
  )
endif()

# =============================================================================
# install header file
if(NOT MSVC)
  install(FILES glad.h khrplatform.h
          DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/GameEngine/ThirdPartySDKs
  )
else()
  install(FILES glad.h khrplatform.h DESTINATION GameEngine/ThirdPartySDKs/glad)
endif()

# =============================================================================
# generate and install export file
if(NOT MSVC)
  install(
    EXPORT GladTargets
    FILE GladTargets.cmake
    NAMESPACE GameEngine::ThirdPartySDKs::
    DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/cmake/GameEngine/ThirdPartySDKs
  )
else()
  install(
    EXPORT GladTargets
    FILE GladTargets.cmake
    NAMESPACE GameEngine::ThirdPartySDKs::
    DESTINATION GameEngine/ThirdPartySDKs/glad
  )
endif()

# =============================================================================
# generate the version file for the config file
write_basic_package_version_file(
  "${CMAKE_CURRENT_BINARY_DIR}/gladConfigVersion.cmake"
  VERSION "1.0.0"
  COMPATIBILITY AnyNewerVersion
)

# =============================================================================
# create config file
if(NOT MSVC)
  configure_package_config_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/Config.cmake.in
    "${CMAKE_CURRENT_BINARY_DIR}/gladConfig.cmake" INSTALL_DESTINATION
    ${CMAKE_INSTALL_DATAROOTDIR}/cmake/glad NO_CHECK_REQUIRED_COMPONENTS_MACRO
  )
else()
  configure_package_config_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/Config.cmake.in
    "${CMAKE_CURRENT_BINARY_DIR}/gladConfig.cmake" INSTALL_DESTINATION
    GameEngine/ThirdPartySDKs/glad NO_CHECK_REQUIRED_COMPONENTS_MACRO
  )
endif()
# =============================================================================
# install config files
if(NOT MSVC)
  install(FILES "${CMAKE_CURRENT_BINARY_DIR}/gladConfig.cmake"
                "${CMAKE_CURRENT_BINARY_DIR}/gladConfigVersion.cmake"
          DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/cmake/glad
  )
else()
  install(FILES "${CMAKE_CURRENT_BINARY_DIR}/gladConfig.cmake"
                "${CMAKE_CURRENT_BINARY_DIR}/gladConfigVersion.cmake"
          DESTINATION GameEngine/ThirdPartySDKs/glad
  )
endif()
