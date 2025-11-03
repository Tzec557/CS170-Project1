cmake_minimum_required(VERSION 3.10)
project(Puzzle8 CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Option to enable sanitizers
option(ENABLE_SANITIZERS "Enable Address/UndefinedBehavior sanitizers (Debug builds only)" OFF)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()

add_executable(puzzle
    main.cpp
    Node.cpp
  Problem.cpp
  UniformCost.cpp
  AStarMisplaced.cpp
  AStarEuclidean.cpp
)

target_compile_options(puzzle PRIVATE -Wall -Wextra -Wconversion)

if(ENABLE_SANITIZERS)
  if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(puzzle PRIVATE -g -O0 -fsanitize=address,undefined)
    target_link_options(puzzle PRIVATE -fsanitize=address,undefined)
  endif()
endif()
