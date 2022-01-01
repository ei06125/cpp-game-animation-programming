# =============================================================================
if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)

  cmake_minimum_required(VERSION 3.21)
  project(AnimationSystemProject)

  if(POLICY CMP0077)
    cmake_policy(SET CMP0077 NEW)
  endif()

  if(NOT MSVC)
    include(GNUInstallDirs)
  else()
    set(CMAKE_INSTALL_PREFIX "C:/dev/AnimationProject")
  endif()

  include(CMakePackageConfigHelpers)

  set(CMAKE_DEBUG_POSTFIX d)

  # import glad
  set(glad_DIR "C://dev/AnimationProject/GameEngine/ThirdPartySDKs/glad")
  find_package(glad 1.0 REQUIRED)

  # import cgltf
  set(cgltf_DIR "C://dev/AnimationProject/GameEngine/ThirdPartySDKs/cgltf")
  find_package(cgltf 1.0 REQUIRED)

  # import Math Library
  set(MathLibrary_DIR
      "C://dev/AnimationProject/GameEngine/CoreSystems/MathLibrary"
  )
  find_package(MathLibrary 1.0 REQUIRED)

  # import Renderer Engine
  set(RendererEngine_DIR "C://dev/AnimationProject/GameEngine/RendererEngine")
  find_package(RendererEngine 1.0 REQUIRED)

endif()

# =============================================================================
# create library
add_library(AnimationSystem SHARED)

file(GLOB_RECURSE AnimationSystem_SOURCES "*.cpp")
file(GLOB_RECURSE AnimationSystem_HEADERS "*.[h|hpp]")
message(DEBUG "AnimationSystem_SOURCES: ${AnimationSystem_SOURCES}")
message(DEBUG "AnimationSystem_HEADERS: ${AnimationSystem_HEADERS}")
target_sources(AnimationSystem PRIVATE ${AnimationSystem_SOURCES})

target_link_libraries(
  AnimationSystem
  PUBLIC GameEngine::ThirdPartySDKs::cgltf GameEngine::ThirdPartySDKs::glad
         GameEngine::CoreSystems::MathLibrary GameEngine::RendererEngine
)

set_target_properties(
  AnimationSystem
  PROPERTIES DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX}
             # create a module definition (.def) file with all global symbols
             # found in the
             # input .obj files for a SHARED library
             WINDOWS_EXPORT_ALL_SYMBOLS ON
)

target_compile_definitions(AnimationSystem PRIVATE GLAD_GLAPI_EXPORT)

add_library(GameEngine::AnimationSystem ALIAS AnimationSystem)

# =============================================================================
# add include directories
target_include_directories(
  AnimationSystem PUBLIC "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>"
                         $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

# =============================================================================
# install the target and create export-set
if(NOT MSVC)
  install(
    TARGETS AnimationSystem
    EXPORT AnimationSystemTargets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}/GameEngine
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}/GameEngine
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}/GameEngine
    INCLUDES
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/GameEngine
  )
else()
  install(
    TARGETS AnimationSystem
    EXPORT AnimationSystemTargets
    LIBRARY DESTINATION GameEngine/AnimationSystem
    ARCHIVE DESTINATION GameEngine/AnimationSystem
    RUNTIME DESTINATION GameEngine/AnimationSystem
    INCLUDES
    DESTINATION GameEngine/AnimationSystem
  )
endif()

# =============================================================================
# install header file
if(NOT MSVC)
  install(FILES ${AnimationSystem_HEADERS}
          DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/GameEngine/
  )
else()
  install(FILES ${AnimationSystem_HEADERS}
          DESTINATION GameEngine/AnimationSystem/
  )
endif()

# =============================================================================
# generate and install export file
if(NOT MSVC)
  install(
    EXPORT AnimationSystemTargets
    FILE AnimationSystemTargets.cmake
    NAMESPACE GameEngine::
    DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/cmake/GameEngine
  )
else()
  install(
    EXPORT AnimationSystemTargets
    FILE AnimationSystemTargets.cmake
    NAMESPACE GameEngine::
    DESTINATION GameEngine/AnimationSystem
  )
endif()

# =============================================================================
# generate the version file for the config file
write_basic_package_version_file(
  "${CMAKE_CURRENT_BINARY_DIR}/AnimationSystemConfigVersion.cmake"
  VERSION "1.0.0"
  COMPATIBILITY AnyNewerVersion
)

# =============================================================================
# create config file
if(NOT MSVC)
  configure_package_config_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/Config.cmake.in
    "${CMAKE_CURRENT_BINARY_DIR}/AnimationSystemConfig.cmake"
    INSTALL_DESTINATION
    ${CMAKE_INSTALL_DATAROOTDIR}/cmake/AnimationSystem
    NO_CHECK_REQUIRED_COMPONENTS_MACRO
  )
else()
  configure_package_config_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/Config.cmake.in
    "${CMAKE_CURRENT_BINARY_DIR}/AnimationSystemConfig.cmake"
    INSTALL_DESTINATION
    GameEngine/AnimationSystem
    NO_CHECK_REQUIRED_COMPONENTS_MACRO
  )
endif()

# =============================================================================
# install config files
if(NOT MSVC)
  install(FILES "${CMAKE_CURRENT_BINARY_DIR}/AnimationSystemConfig.cmake"
                "${CMAKE_CURRENT_BINARY_DIR}/AnimationSystemConfigVersion.cmake"
          DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/cmake/AnimationSystem
  )
else()
  install(FILES "${CMAKE_CURRENT_BINARY_DIR}/AnimationSystemConfig.cmake"
                "${CMAKE_CURRENT_BINARY_DIR}/AnimationSystemConfigVersion.cmake"
          DESTINATION GameEngine/AnimationSystem
  )
endif()
