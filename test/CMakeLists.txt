# Download and unpack googletest at configure time
configure_file(${PROJECT_SOURCE_DIR}/cmake/third_party/googletest.cmake googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()

# Prevent overriding the parent project's compiler/linker
# settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/googletest-src
                 ${CMAKE_CURRENT_BINARY_DIR}/googletest-build
                 EXCLUDE_FROM_ALL)

file(GLOB UNIT_TEST_FILES "unit/**.cpp")

foreach(FILE ${UNIT_TEST_FILES})
    get_filename_component(TEST_CASE ${FILE} NAME_WE)

    add_executable(${TEST_CASE} ${FILE})
    target_link_libraries(${TEST_CASE} ${PROJECT_NAME}_header_only gtest_main)

    add_test(
        NAME "${TEST_CASE}"
        COMMAND ${TEST_CASE} --no-skip
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    )
endforeach()
