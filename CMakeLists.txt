cmake_minimum_required(VERSION 3.5)

project(
  "dont"
  VERSION 0.0.0
  DESCRIPTION "A collection of C++ template (metaprogramming) utilities that I often need, but don't want to have to re-implement for the 1000th time."
)

#############################################################################
# Library
#############################################################################

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR})
set(CMAKE_CXX_FLAGS "-std=c++17 -O3")

add_library(${PROJECT_NAME}_core INTERFACE)
target_compile_features(${PROJECT_NAME}_core INTERFACE cxx_std_17)
target_include_directories(
  ${PROJECT_NAME}_core
  INTERFACE
    $<BUILD_INTERFACE:${${PROJECT_NAME}_SOURCE_DIR}/core/include>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

add_library(${PROJECT_NAME}_stl INTERFACE)
target_compile_features(${PROJECT_NAME}_stl INTERFACE cxx_std_17)
target_include_directories(
  ${PROJECT_NAME}_stl
  INTERFACE
    ${PROJECT_NAME}_core
    $<BUILD_INTERFACE:${${PROJECT_NAME}_SOURCE_DIR}/stl/include>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)
target_link_libraries(
  ${PROJECT_NAME}_stl
  INTERFACE
    ${PROJECT_NAME}_core
)


include(GNUInstallDirs)
install(TARGETS ${PROJECT_NAME}_core
        EXPORT ${PROJECT_NAME}_Targets
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})


#############################################################################
# PackageConfig
#############################################################################

include(CMakePackageConfigHelpers)
write_basic_package_version_file("${PROJECT_NAME}ConfigVersion.cmake"
                                 VERSION ${PROJECT_VERSION}
                                 COMPATIBILITY SameMajorVersion)

configure_package_config_file(
  "${PROJECT_SOURCE_DIR}/cmake/${PROJECT_NAME}Config.cmake.in"
  "${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
  INSTALL_DESTINATION
  ${CMAKE_INSTALL_DATAROOTDIR}/${PROJECT_NAME}/cmake)

install(EXPORT ${PROJECT_NAME}_Targets
        FILE ${PROJECT_NAME}Targets.cmake
        NAMESPACE ${PROJECT_NAME}::
        DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/${PROJECT_NAME}/cmake)
install(FILES "${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
              "${PROJECT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
        DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/${PROJECT_NAME}/cmake)
install(DIRECTORY ${PROJECT_SOURCE_DIR}/include DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})


#############################################################################
# Tests
#############################################################################

if(DONT_ENABLE_TESTING)
  set(CMAKE_WARN_DEPRECATED OFF CACHE BOOL "" FORCE)
  enable_testing()
  add_subdirectory(test)
endif()