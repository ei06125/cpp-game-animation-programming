# =============================================================================
if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
  cmake_minimum_required(VERSION 3.21)
  project(cgltf)
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
add_library(cgltf SHARED cgltf.cpp)

add_library(GameEngine::ThirdPartySDKs::cgltf ALIAS cgltf)

set_target_properties(cgltf PROPERTIES WINDOWS_EXPORT_ALL_SYMBOLS ON)

target_compile_definitions(cgltf PRIVATE GLAD_GLAPI_EXPORT)

# =============================================================================
# add include directories
target_include_directories(
  cgltf PUBLIC "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>"
               $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

# =============================================================================
# install the target and create export-set
if(NOT MSVC)
  install(
    TARGETS cgltf
    EXPORT cgltfTargets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}/GameEngine/ThirdPartySDKs
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}/GameEngine/ThirdPartySDKs
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}/GameEngine/ThirdPartySDKs
    INCLUDES
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/GameEngine/ThirdPartySDKs
  )
else()
  install(
    TARGETS cgltf
    EXPORT cgltfTargets
    LIBRARY DESTINATION GameEngine/ThirdPartySDKs/cgltf
    ARCHIVE DESTINATION GameEngine/ThirdPartySDKs/cgltf
    RUNTIME DESTINATION GameEngine/ThirdPartySDKs/cgltf
    INCLUDES
    DESTINATION GameEngine/ThirdPartySDKs/cgltf
  )
endif()

# =============================================================================
# install header file
if(NOT MSVC)
  install(FILES cgltf.h
          DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/GameEngine/ThirdPartySDKs/
  )
else()
  install(FILES cgltf.h DESTINATION GameEngine/ThirdPartySDKs/cgltf/)
endif()

# =============================================================================
# generate and install export file
if(NOT MSVC)
  install(
    EXPORT cgltfTargets
    FILE cgltfTargets.cmake
    NAMESPACE GameEngine::ThirdPartySDKs::
    DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/cmake/GameEngine/ThirdPartySDKs
  )
else()
  install(
    EXPORT cgltfTargets
    FILE cgltfTargets.cmake
    NAMESPACE GameEngine::ThirdPartySDKs::
    DESTINATION GameEngine/ThirdPartySDKs/cgltf
  )
endif()

# =============================================================================
# generate the version file for the config file
write_basic_package_version_file(
  "${CMAKE_CURRENT_BINARY_DIR}/cgltfConfigVersion.cmake"
  VERSION "1.0.0"
  COMPATIBILITY AnyNewerVersion
)

# =============================================================================
# create config file
if(NOT MSVC)
  configure_package_config_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/Config.cmake.in
    "${CMAKE_CURRENT_BINARY_DIR}/cgltfConfig.cmake" INSTALL_DESTINATION
    ${CMAKE_INSTALL_DATAROOTDIR}/cmake/cgltf NO_CHECK_REQUIRED_COMPONENTS_MACRO
  )
else()
  configure_package_config_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/Config.cmake.in
    "${CMAKE_CURRENT_BINARY_DIR}/cgltfConfig.cmake" INSTALL_DESTINATION
    GameEngine/ThirdPartySDKs/cgltf NO_CHECK_REQUIRED_COMPONENTS_MACRO
  )
endif()

# =============================================================================
# install config files
if(NOT MSVC)
  install(FILES "${CMAKE_CURRENT_BINARY_DIR}/cgltfConfig.cmake"
                "${CMAKE_CURRENT_BINARY_DIR}/cgltfConfigVersion.cmake"
          DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/cmake/cgltf
  )
else()
  install(FILES "${CMAKE_CURRENT_BINARY_DIR}/cgltfConfig.cmake"
                "${CMAKE_CURRENT_BINARY_DIR}/cgltfConfigVersion.cmake"
          DESTINATION GameEngine/ThirdPartySDKs/cgltf
  )
endif()
