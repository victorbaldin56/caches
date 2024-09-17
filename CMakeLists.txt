cmake_minimum_required(VERSION 3.14)
project("problem_lc")

add_library(lc INTERFACE)
target_include_directories(lc INTERFACE ${CMAKE_SOURCE_DIR}/include)

include(FetchContent)
FetchContent_Declare(
  googletest
  # Specify the commit you depend on and update it regularly.
  URL https://github.com/google/googletest/archive/5376968f6948923e2411081fd9372e71a59d8e77.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

SET(APPS lfu;belady)

foreach(APP ${APPS})
  add_executable(${APP} drivers/${APP}_cache.cc)
  target_include_directories(${APP} PRIVATE common)
  target_link_libraries(${APP} lc)
  target_compile_features(${APP} PRIVATE cxx_std_14)
  target_compile_options(${APP} PRIVATE $<$<CONFIG:DEBUG>:-fsanitize=address> -Wall -Wextra -Wswitch-enum)
  target_link_options(${APP} PRIVATE $<$<CONFIG:DEBUG>:-fsanitize=address>)
endforeach()

# Unit test build
add_executable(test unit_tests/unit_tests.cc)
target_link_libraries(test lc;gtest_main)
target_include_directories(test PRIVATE common)
target_compile_features(test PRIVATE cxx_std_14)
target_compile_options(test PRIVATE $<$<CONFIG:DEBUG>:-fsanitize=address> -Wall -Wextra -Wswitch-enum)
target_link_options(test PRIVATE $<$<CONFIG:DEBUG>:-fsanitize=address>)
