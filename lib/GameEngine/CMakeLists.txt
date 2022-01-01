# =============================================================================
if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
  cmake_minimum_required(VERSION 3.21)
  project(GameEngineProject)
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
endif()

# =============================================================================
# add components add_subdirectory(ThirdPartySDKs) add_subdirectory(CoreSystems)
# add_subdirectory(RendererEngine) add_subdirectory(AnimationSystem)

# =============================================================================
# create library
add_library(GameEngine INTERFACE)

set(GameEngine_HEADERS "Application.h" "GameEngine.hpp")
message(DEBUG "GameEngine_HEADERS: ${GameEngine_HEADERS}")

target_link_libraries(
  GameEngine
  INTERFACE # Third Party SDKs
            GameEngine::ThirdPartySDKs::glad
            GameEngine::ThirdPartySDKs::cgltf
            GameEngine::ThirdPartySDKs::nuklear
            GameEngine::ThirdPartySDKs::stb_image
            # Sub systems
            GameEngine::RendererEngine
            GameEngine::AnimationSystem
)

set_target_properties(GameEngine PROPERTIES WINDOWS_EXPORT_ALL_SYMBOLS ON)

target_compile_definitions(GameEngine INTERFACE GLAD_GLAPI_EXPORT)

add_library(AnimationProject::GameEngine ALIAS GameEngine)

# =============================================================================
# add include directories
target_include_directories(
  GameEngine INTERFACE "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>"
                       $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

# =============================================================================
# install the target and create export-set
if(NOT MSVC)
  install(
    TARGETS GameEngine
    EXPORT GameEngineTargets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    INCLUDES
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
  )
else()
  install(
    TARGETS GameEngine
    EXPORT GameEngineTargets
    LIBRARY DESTINATION GameEngine
    ARCHIVE DESTINATION GameEngine
    RUNTIME DESTINATION GameEngine
    INCLUDES
    DESTINATION GameEngine
  )
endif()

# =============================================================================
# install header file
if(NOT MSVC)
  install(FILES ${GameEngine_HEADERS} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
else()
  install(FILES ${GameEngine_HEADERS} DESTINATION GameEngine)
endif()

# =============================================================================
# generate and install export file
if(NOT MSVC)
  install(
    EXPORT GameEngineTargets
    FILE GameEngineTargets.cmake
    NAMESPACE AnimationProject::
    DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/cmake
  )
else()
  install(
    EXPORT GameEngineTargets
    FILE GameEngineTargets.cmake
    NAMESPACE AnimationProject::
    DESTINATION GameEngine
  )
endif()

# =============================================================================
# generate the version file for the config file
write_basic_package_version_file(
  "${CMAKE_CURRENT_BINARY_DIR}/GameEngineConfigVersion.cmake"
  VERSION "1.0.0"
  COMPATIBILITY AnyNewerVersion
)

# =============================================================================
# create config file
if(NOT MSVC)
  configure_package_config_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/Config.cmake.in
    "${CMAKE_CURRENT_BINARY_DIR}/GameEngineConfig.cmake" INSTALL_DESTINATION
    ${CMAKE_INSTALL_DATAROOTDIR}/cmake NO_CHECK_REQUIRED_COMPONENTS_MACRO
  )
else()
  configure_package_config_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/Config.cmake.in
    "${CMAKE_CURRENT_BINARY_DIR}/GameEngineConfig.cmake" INSTALL_DESTINATION
    GameEngine NO_CHECK_REQUIRED_COMPONENTS_MACRO
  )
endif()

# =============================================================================
# install config files
if(NOT MSVC)
  install(FILES "${CMAKE_CURRENT_BINARY_DIR}/GameEngineConfig.cmake"
                "${CMAKE_CURRENT_BINARY_DIR}/GameEngineConfigVersion.cmake"
          DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/cmake/
  )
else()
  install(FILES "${CMAKE_CURRENT_BINARY_DIR}/GameEngineConfig.cmake"
                "${CMAKE_CURRENT_BINARY_DIR}/GameEngineConfigVersion.cmake"
          DESTINATION GameEngine
  )
endif()
