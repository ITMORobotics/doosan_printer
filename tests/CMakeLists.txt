cmake_minimum_required(VERSION 3.10)

# set the project name
project(doosan_gcode_tests)

find_package(Boost REQUIRED COMPONENTS system)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include_directories(
  ..
  ${Boost_INCLUDE_DIR}
)
link_directories(../common/lib/noetic/x86_64)

# if(TARGET doosan_gcode)
  add_executable(leshka leshka.cpp)
  target_link_libraries(leshka gpr)

  add_executable(test_gcode test_gcode.cpp)
  target_link_libraries(test_gcode gpr doosan_gcode DRFL)

  add_executable(tcp_printer tcp_printer.cpp)
  target_link_libraries(tcp_printer gpr doosan_gcode DRFL ${Boost_LIBRARIES})

  # add_executable(dima dima.cpp)
  # target_link_libraries(dima gpr doosan_gcode)
# endif()
