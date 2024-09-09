cmake_minimum_required(VERSION 3.11)
project("problem_lc")

add_library(lc INTERFACE)
target_include_directories(lc INTERFACE include)

SET(SRCS
  driver/main.cc
)

add_executable(lcdriver ${SRCS})
target_link_libraries(lcdriver lc)
