# =============================================================================
if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
  cmake_minimum_required(VERSION 3.21)
  if(POLICY CMP0077)
    cmake_policy(SET CMP0077 NEW)
  endif()
  project(RendererEngine)
  if(NOT MSVC)
    include(GNUInstallDirs)
  else()
    set(CMAKE_INSTALL_PREFIX "C:/dev/AnimationProject")
  endif()
  include(CMakePackageConfigHelpers)
  set(CMAKE_DEBUG_POSTFIX d)
endif()

# =============================================================================
# create library
add_library(RendererEngine SHARED)

file(GLOB_RECURSE RendererEngine_SOURCES "*.cpp")
file(GLOB_RECURSE RendererEngine_HEADERS "*.[h|hpp]")
message(DEBUG "RendererEngine_SOURCES: ${RendererEngine_SOURCES}")
message(DEBUG "RendererEngine_HEADERS: ${RendererEngine_HEADERS}")
target_sources(RendererEngine PRIVATE ${RendererEngine_SOURCES})

# import glad
set(glad_DIR "C://dev/AnimationProject/GameEngine/ThirdPartySDKs/glad")
find_package(glad 1.0 REQUIRED)

# import stb_image
set(stb_image_DIR
    "C://dev/AnimationProject/GameEngine/ThirdPartySDKs/stb_image"
)
find_package(stb_image 1.0 REQUIRED)

# import Math Library
set(MathLibrary_DIR
    "C://dev/AnimationProject/GameEngine/CoreSystems/MathLibrary"
)
find_package(MathLibrary 1.0 REQUIRED)

target_link_libraries(
  RendererEngine
  PUBLIC GameEngine::ThirdPartySDKs::glad GameEngine::ThirdPartySDKs::stb_image
         GameEngine::CoreSystems::MathLibrary
)

set_target_properties(
  RendererEngine
  PROPERTIES DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX}
             # create a module definition (.def) file with all global symbols
             # found in the
             # input .obj files for a SHARED library
             WINDOWS_EXPORT_ALL_SYMBOLS ON
)

target_compile_definitions(RendererEngine PRIVATE GLAD_GLAPI_EXPORT)

add_library(GameEngine::RendererEngine ALIAS RendererEngine)

# =============================================================================
# add include directories
target_include_directories(
  RendererEngine PUBLIC "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>"
                        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

# =============================================================================
# install the target and create export-set
if(NOT MSVC)
  install(
    TARGETS RendererEngine
    EXPORT RendererEngineTargets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}/GameEngine
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}/GameEngine
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}/GameEngine
    INCLUDES
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/GameEngine
  )
else()
  install(
    TARGETS RendererEngine
    EXPORT RendererEngineTargets
    LIBRARY DESTINATION GameEngine/RendererEngine
    ARCHIVE DESTINATION GameEngine/RendererEngine
    RUNTIME DESTINATION GameEngine/RendererEngine
    INCLUDES
    DESTINATION GameEngine/RendererEngine
  )
endif()

# =============================================================================
# install header file
if(NOT MSVC)
  install(FILES ${RendererEngine_HEADERS}
          DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/GameEngine/
  )
else()
  install(FILES ${RendererEngine_HEADERS}
          DESTINATION GameEngine/RendererEngine/
  )
endif()

# =============================================================================
# generate and install export file
if(NOT MSVC)
  install(
    EXPORT RendererEngineTargets
    FILE RendererEngineTargets.cmake
    NAMESPACE GameEngine::
    DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/cmake/GameEngine/
  )
else()
  install(
    EXPORT RendererEngineTargets
    FILE RendererEngineTargets.cmake
    NAMESPACE GameEngine::
    DESTINATION GameEngine/RendererEngine
  )
endif()

# =============================================================================
# generate the version file for the config file
write_basic_package_version_file(
  "${CMAKE_CURRENT_BINARY_DIR}/RendererEngineConfigVersion.cmake"
  VERSION "1.0.0"
  COMPATIBILITY AnyNewerVersion
)

# =============================================================================
# create config file
if(NOT MSVC)
  configure_package_config_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/Config.cmake.in
    "${CMAKE_CURRENT_BINARY_DIR}/RendererEngineConfig.cmake"
    INSTALL_DESTINATION
    ${CMAKE_INSTALL_DATAROOTDIR}/cmake/RendererEngine
    NO_CHECK_REQUIRED_COMPONENTS_MACRO
  )
else()
  configure_package_config_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/Config.cmake.in
    "${CMAKE_CURRENT_BINARY_DIR}/RendererEngineConfig.cmake"
    INSTALL_DESTINATION
    GameEngine/RendererEngine
    NO_CHECK_REQUIRED_COMPONENTS_MACRO
  )
endif()

# =============================================================================
# install config files
if(NOT MSVC)
  install(FILES "${CMAKE_CURRENT_BINARY_DIR}/RendererEngineConfig.cmake"
                "${CMAKE_CURRENT_BINARY_DIR}/RendererEngineConfigVersion.cmake"
          DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/cmake/RendererEngine
  )
else()
  install(FILES "${CMAKE_CURRENT_BINARY_DIR}/RendererEngineConfig.cmake"
                "${CMAKE_CURRENT_BINARY_DIR}/RendererEngineConfigVersion.cmake"
          DESTINATION GameEngine/RendererEngine
  )
endif()
