cmake_minimum_required(VERSION 3.10)

# set the project name
project(doosan_gcode VERSION 1.0)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(gpr)
add_subdirectory(DRFLn)

include_directories(
  ./gpr/src/
  ./src
  ./DRFLn/include
)

link_directories(
  ./DRFLn/lib/noetic/x86_64
)

add_library(doosan_gcode
  src/doosan_gcode.cpp
  src/commands/G_commands.cpp
  src/commands/M_commands.cpp
)
target_link_libraries(doosan_gcode gpr DRFL_robot)

add_subdirectory(tests)
