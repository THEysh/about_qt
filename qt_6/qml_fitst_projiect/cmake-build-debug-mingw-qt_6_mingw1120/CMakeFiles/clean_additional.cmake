# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\qml_fitst_projiect_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\qml_fitst_projiect_autogen.dir\\ParseCache.txt"
  "qml_fitst_projiect_autogen"
  )
endif()
