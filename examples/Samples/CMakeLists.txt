# =============================================================================
if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
  cmake_minimum_required(VERSION 3.21)
  project(AnimationTechDemoProject)

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

  set(ROOT_DIR "../..")

  # import GameEngine
  set(GameEngine_DIR "C://dev/AnimationProject/GameEngine")
  find_package(GameEngine 1.0 REQUIRED)

endif()

# =============================================================================
# create executable
add_executable(TechDemo)

file(GLOB_RECURSE TechDemo_SOURCES "*.cpp")
file(GLOB_RECURSE TechDemo_HEADERS "*.[h|hpp]")
message(DEBUG "TechDemo_SOURCES: ${TechDemo_SOURCES}")
message(DEBUG "TechDemo_HEADERS: ${TechDemo_HEADERS}")
target_sources(TechDemo PRIVATE ${TechDemo_SOURCES})

target_link_libraries(
  TechDemo
  PRIVATE opengl32
          Shcore
          # AnimationProject::GameEngine GameEngine::ThirdPartySDKs::glad
          # GameEngine::ThirdPartySDKs::cgltf
          # GameEngine::ThirdPartySDKs::nuklear
          # GameEngine::ThirdPartySDKs::stb_image GameEngine::RendererEngine
          # GameEngine::AnimationSystem
          AnimationProject::GameEngine
)

target_include_directories(
  TechDemo PRIVATE ${ROOT_DIR}/examples ${GameEngine_INCLUDE}
)

target_compile_definitions(TechDemo PRIVATE GLAD_GLAPI_EXPORT)

set_target_properties(TechDemo PROPERTIES DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX})

add_custom_command(
  TARGET TechDemo
  POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/Assets
          $<TARGET_FILE_DIR:TechDemo>/Assets
  COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/Shaders
          $<TARGET_FILE_DIR:TechDemo>/Shaders
  COMMENT "Copying Assets and Shaders into working directory"
  VERBATIM
)

# =============================================================================
# add include directories
target_include_directories(
  TechDemo PRIVATE "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>"
                   $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)
