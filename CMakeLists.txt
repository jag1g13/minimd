cmake_minimum_required(VERSION 2.8.4)
project(minimd)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O3")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g -Og")

# Find libxdrfile - compile it if not present - replaces GROMACS library
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
find_library(XDRFILE_LIBRARY NAMES xdrfile
             PATHS /usr/lib /usr/local/lib ${CMAKE_CURRENT_SOURCE_DIR}/lib)
if(XDRFILE_LIBRARY_FOUND)
    MESSAGE("Found libxdrfile: ${XDRFILE_LIBRARY}")
    set (EXTRA_LIBS ${EXTRA_LIBS} ${XDRFILE_LIBRARY})
else()
    MESSAGE("Cannot find libxdrfile, including in compile")
    set(LIBRARY_OUTPUT_DIRCTORY lib)
    add_library(xdrfile STATIC lib/xdrfile/xdrfile.c lib/xdrfile/xdrfile_xtc.c)
    set (EXTRA_LIBS ${EXTRA_LIBS} xdrfile)
endif()

set(SOURCE_FILES
        main.cpp
        md.cpp
        src/vec3d.cpp
        src/XTCOutput.cpp
        src/integrator-leapfrog.cpp
        src/integrator-verlet.cpp
        src/thermostat-vrescale.cpp
        src/nonbond-lj.cpp
        src/bond-length-harmonic.cpp)

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include")
add_executable(minimd ${SOURCE_FILES})
target_link_libraries(minimd ${EXTRA_LIBS})
