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

SET(SRCS
  driver/main.cc
)

add_executable(lcdriver ${SRCS})
target_link_libraries(lcdriver lc)
target_compile_features(lcdriver PRIVATE cxx_std_14)
target_compile_options(lcdriver PRIVATE $<$<CONFIG:DEBUG>:-fsanitize=address> -Wall -Wextra -Wswitch-enum)
target_compile_definitions(lcdriver PRIVATE $<$<CONFIG:DEBUG>:TESTING>)
target_link_options(lcdriver PRIVATE $<$<CONFIG:DEBUG>:-fsanitize=address>)
target_link_libraries(lcdriver gtest_main)

add_test(NAME lctest COMMAND lcdriver)
