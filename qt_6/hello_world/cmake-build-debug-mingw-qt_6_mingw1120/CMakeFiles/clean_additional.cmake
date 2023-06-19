# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\hello_world_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\hello_world_autogen.dir\\ParseCache.txt"
  "hello_world_autogen"
  )
endif()
