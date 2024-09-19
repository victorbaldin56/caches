cmake_minimum_required(VERSION 3.14)
project("problem_lc")

add_library(lc INTERFACE)
target_include_directories(lc INTERFACE ${CMAKE_SOURCE_DIR}/include)

SET(APPS lfu;belady)

foreach(APP ${APPS})
  add_executable(${APP} drivers/${APP}_cache.cc)
  target_include_directories(${APP} PRIVATE common)
  target_link_libraries(${APP} lc)
  target_compile_features(${APP} PRIVATE cxx_std_14)

  if (${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang" OR ${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU")
    target_compile_options(${APP} PRIVATE $<$<CONFIG:DEBUG>:-fsanitize=address,undefined,leak> -Wall -Wextra -Wswitch-enum)
    target_link_options(${APP} PRIVATE $<$<CONFIG:DEBUG>:-fsanitize=address,undefined,leak>)
  endif()
endforeach()

if (${CMAKE_BUILD_TYPE} STREQUAL "Debug")
  include(FetchContent)
  FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        "origin/main"
  )
  # For Windows: Prevent overriding the parent project's compiler/linker settings
  set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
  FetchContent_MakeAvailable(googletest)

  # Unit test build
  add_executable(test unit_tests/unit_tests.cc)
  target_link_libraries(test lc;gtest_main)
  target_include_directories(test PRIVATE common)
  target_compile_features(test PRIVATE cxx_std_14)
endif()
