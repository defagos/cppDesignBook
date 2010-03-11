# CMake build rules for C++ design book and examples
# --------------------------------------------------
# Using CMake, this file generates the files needed to build the book and its examples in a 
# platform-independent way. You will need to install CMake first (www.cmake.org).
#
# Usage: CMake supports out-of-source and in-source builds. Out-of-source builds are strongly
#        recommended since they keep the source tree intact:
#    i) Out-of-source build: Create a directory somewhere, switch to this directory and execute
#                            cmake from there, giving it the directory where this CMakeLists.txt
#                            file is located. Usually the out-of-source build takes place
#                            in a subdirectory created in the same directory as the CMakeLists.txt
#                            file, e.g.:
#                                    cd <main CMakeLists.txt directory>
#                                    mkdir build
#                                    cd build
#                                    cmake ..
#    ii) In-source build: This is the degenerated case where cmake is executed directly from
#        the directory where CMakeLists.txt is located, i.e.:
#                                    cd <main CMakeLists.txt directory>
#                                    cmake .
#
# Use the cmake -G flag if you want to set the makefile generator manually.
#
# Supported configurations: Debug, Release, RelWithDebInfo, MinSizeRel

CMAKE_MINIMUM_REQUIRED(VERSION 2.6 FATAL_ERROR)
PROJECT(cppDesignBook)

# Final binary products are separated using three directory levels for easy identification, as
# follows:
#   - 1st directory level: lib for static libraries, dll for dynamic link libraries and bin
#                          for executables
#   - 2nd directory: platform (MSVC10x86 and MSVC10x64 for Visual C++ 2010 compiler 32 / 64 bits,
#                    MinGW for MinGW, etc.)
#   - 3rd directory level: A subdirectory is created for each configuration (Debug, Release,
#                          RelWithDebInfo, MinSizeRel)
# A remark about the Visual Studio solution generators: Though a single solution can support
# 32 and 64-bit platforms when created by hand, CMake generators cannot. If we want both solution
# flavors, we therefore need two cmake runs with different generators.
# Other generators conform to the "autotools convention of one configuration per build tree"
# (see http://www.cmake.org/pipermail/cmake/2004-July/005286.html)

# Visual Studio 2010 solution (32-bits)
IF(${CMAKE_GENERATOR} STREQUAL "Visual Studio 10")
    SET(CONST_PLATFORM MSVC10x86)
    # The Visual Studio solution generators automatically generate separate output directories for
    # each configuration. We do not need to generate the 3rd directory level
    SET(OUTPUT_SUBDIR ${CONST_PLATFORM})
# Visual Studio 2010 solution (64-bits)
ELSEIF(${CMAKE_GENERATOR} STREQUAL "Visual Studio 10 Win64")
    SET(CONST_PLATFORM MSVC10x64)
    # The Visual Studio solution generators automatically generate separate output directories for
    # each configuration. We do not need to generate the 3rd directory level
    SET(OUTPUT_SUBDIR ${CONST_PLATFORM})
# Visual Studio 2008 solution (32-bits)
ELSEIF(${CMAKE_GENERATOR} STREQUAL "Visual Studio 9 2008")
    SET(CONST_PLATFORM MSVC9x86)
    # The Visual Studio solution generators automatically generate separate output directories for
    # each configuration. We do not need to generate the 3rd directory level
    SET(OUTPUT_SUBDIR ${CONST_PLATFORM})
# Visual Studio 2008 solution (64-bits)
ELSEIF(${CMAKE_GENERATOR} STREQUAL "Visual Studio 9 2008 Win64")
    SET(CONST_PLATFORM MSVC9x64)
    # The Visual Studio solution generators automatically generate separate output directories for
    # each configuration. We do not need to generate the 3rd directory level
    SET(OUTPUT_SUBDIR ${CONST_PLATFORM})
# MinGW compiler (32-bits)
ELSEIF(${CMAKE_GENERATOR} STREQUAL "MinGW Makefiles")
    SET(CONST_PLATFORM MinGW)
    # The build configuration must be explicitly specified
    IF (NOT CMAKE_BUILD_TYPE)
        MESSAGE(FATAL_ERROR "Missing configuration. Add -DCMAKE_BUILD_TYPE when calling cmake")
    ENDIF()
    # We need to generate all directory levels
    SET(OUTPUT_SUBDIR ${CONST_PLATFORM}/${CMAKE_BUILD_TYPE})
# Unix Makefiles
ELSEIF (${CMAKE_GENERATOR} STREQUAL "Unix Makefiles")
    SET(CONST_PLATFORM UnixMakefiles)
    # The build configuration must be explicitly specified
    IF (NOT CMAKE_BUILD_TYPE)
        MESSAGE(FATAL_ERROR "Missing configuration. Add -DCMAKE_BUILD_TYPE when calling cmake")
    ENDIF()
    # We need to generate all directory levels
    SET(OUTPUT_SUBDIR ${CONST_PLATFORM}/${CMAKE_BUILD_TYPE})
# For all generators we do not support officially: error
ELSE()
    MESSAGE(FATAL_ERROR "The generator ${CMAKE_GENERATOR} is currently not supported")
ENDIF()

# Set the output directories
SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib/${OUTPUT_SUBDIR})
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/dll/${OUTPUT_SUBDIR})
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/${OUTPUT_SUBDIR})

# Add projects
ADD_SUBDIRECTORY(src/stlContainerChapter)
