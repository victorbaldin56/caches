cmake_minimum_required(VERSION 3.11)
project("problem_lc")

add_library(lc INTERFACE)
target_include_directories(lc INTERFACE ${CMAKE_SOURCE_DIR}/include)

SET(SRCS
  driver/main.cc
)

add_executable(lcdriver ${SRCS})
target_link_libraries(lcdriver lc)
target_compile_features(lcdriver PRIVATE cxx_std_11)
target_compile_options(lcdriver PRIVATE $<$<CONFIG:DEBUG>:-fsanitize=address> -Wall -Wextra -Wswitch-enum)
target_link_options(lcdriver PRIVATE $<$<CONFIG:DEBUG>:-fsanitize=address>)
