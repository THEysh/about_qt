# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\boll_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\boll_autogen.dir\\ParseCache.txt"
  "boll_autogen"
  )
endif()
