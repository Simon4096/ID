cmake_minimum_required(VERSION 3.5)
project(Deidentify)

set(CMAKE_BUILD_TYPE Debug)

# Check Dependencies
include(cmake/dependencies.cmake)
include_directories(${Dependencies_INCLUDE_DIRS})

# Compile
add_executable(Deidentify main.cpp)
target_link_libraries(Deidentify PUBLIC ${Dependencies_LIBRARIES} stdc++fs)
set_target_properties(Deidentify PROPERTIES
    CXX_STANDARD 14
	OUTPUT_NAME "ImageDeidentify"
    )
