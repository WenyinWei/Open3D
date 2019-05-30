# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

project ("OpenCLCUDA")
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/../bin) 
find_package(opencl REQUIRED)
MESSAGE(${OpenCL_LIBRARIES})
MESSAGE(${OpenCL_LIBRARY})
INCLUDE_DIRECTORIES(${OpenCL_INCLUDE_DIRS}) 
LINK_LIBRARIES(${OpenCL_LIBRARY})

#INCLUDE_DIRECTORIES(${OPENCL_INCLUDE_DIR})
# Add source to this project's executable.
add_executable (OpenCLCUDA "OpenCLCUDA.cpp")

add_executable (CheckGPU "CheckGPU.cpp")
# TODO: Add tests and install targets if needed.
# target_link_libraries(OpenCLCUDA ${OpenCL_LIBRARY})