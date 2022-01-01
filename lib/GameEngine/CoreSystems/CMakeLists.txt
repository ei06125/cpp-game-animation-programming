add_subdirectory(MathLibrary)

# # set version
# set(version 1.0.0)

# # generate the version file for the config file
# write_basic_package_version_file(
#   "${CMAKE_CURRENT_BINARY_DIR}/CoreSystemsConfigVersion.cmake"
#   VERSION "${version}"
#   COMPATIBILITY AnyNewerVersion
# )

# # create config file
# configure_package_config_file(
#   ${CMAKE_CURRENT_SOURCE_DIR}/Config.cmake.in
#   "${CMAKE_CURRENT_BINARY_DIR}/CoreSystemsConfig.cmake" INSTALL_DESTINATION
#   ${CMAKE_INSTALL_LIBDIR}/cmake/CoreSystems NO_CHECK_REQUIRED_COMPONENTS_MACRO
# )

# # install config files
# install(FILES "${CMAKE_CURRENT_BINARY_DIR}/CoreSystemsConfig.cmake"
#               "${CMAKE_CURRENT_BINARY_DIR}/CoreSystemsConfigVersion.cmake"
#         DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/CoreSystems
# )
