#!/bin/bash

#******************************************************
# General CMake (out-of-source) Unix makefile generator
#******************************************************

# User manual
usage() {
    echo
    echo "Generates a directory containing all makefiles for a given enviroment"
    echo
    echo "Usage: `basename $0` ENVIRONMENT CMAKELISTS_DIRECTORY OUTPUT_DIRECTORY"
    echo
    echo "The supported environments are currently: UnixMakefiles"
    echo
}

# Returns the relative path between the paths given as parameters
# Example: path 1 = /this/is/some/path
#          path 2 = /this/is/another/path
#          output = ../../another/path/
# @param $1 first path (absolute or relative)
# @param $2 second path (absolute or relative)
absolute_to_relative_path() {
    # Convert to absolute paths
    abs_path1=`cd $1; pwd`
    abs_path2=`cd $2; pwd`

    # Tokenize the paths into directories
    tokens_arr1=(`echo "$abs_path1" | tr "/" "\n"`)
    tokens_arr2=(`echo "$abs_path2" | tr "/" "\n"`)
    
    # Find the shortest path length
    if [ "${#tokens_arr1[*]}" -lt "${#tokens_arr2[*]}" ]; then
        length=${#tokens_arr1[*]}
    else
        length=${#tokens_arr2[*]}
    fi
    
    # Find the number of common directories
    common_length=0
    while [ "$common_length" -lt "$length" ]
    do
        if [ "${tokens_arr1[$common_length]}" == "${tokens_arr2[$common_length]}" ]; then
            let common_length=common_length+1
        else
            break;
        fi
    done    

    # Build the relative path
    relative_path=""
    
    # For each directory in first path which is not common, add ../
    i=$common_length
    while [ "$i" -lt "${#tokens_arr1[*]}" ]
    do
        relative_path="$relative_path../"
        let i=i+1
    done
    
    # Add each directory specific to the second path
    i=$common_length
    while [ "$i" -lt "${#tokens_arr2[*]}" ]
    do
        relative_path="$relative_path${tokens_arr2[$i]}/"
        let i=i+1
    done
    
    # Return the value to the caller
    echo "$relative_path"
}

# Function for generating the Unix makefiles for a single environment
# @param $1 environment name
generate_unix_makefiles() {
    environment_dir="$OUTPUT_DIR/UnixMakefiles/$1"

    echo
    echo "Generating $1 makefile"
    mkdir -p "$environment_dir"
    cd "$environment_dir"
    
    # Finds the relative path. It would have been easier to pass $CMAKELISTS_DIR
    # to cmake directly, but sadly this does not work under Cygwin. Relative paths
    # work well, though
    cmakelists_relative_path=$(absolute_to_relative_path "$environment_dir" "$CMAKELISTS_DIR")
    
    cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=$1 "$cmakelists_relative_path"
}

# Directory where the script was launched
EXECUTION_DIR=`pwd`

# Check that the maximum number of parameters has not been exceeded
if [ "$#" != "3" ]; then
    usage
    exit 1
fi

# Directory where the main CMakeLists.txt file resides (converted to absolute path)
CMAKELISTS_DIR=`cd $2; pwd`

# Check that it contains a CMakeLists.txt file
if [ ! -f "$CMAKELISTS_DIR/CMakeLists.txt" ]; then
    echo "Error: No CMakeLists.txt file found in $CMAKELISTS_DIR"
    exit 1
fi

# Directory where the output files must be saved (converted to absolute path)
OUTPUT_DIR=`cd $3; pwd`

# Set up the CMake generator according to the environment
if [ "$1" == "UnixMakefiles" ]; then
    GENERATOR_NAME="UnixMakefiles"
else
    usage
    exit 1
fi

# Generate the Unix makefile for all configurations
echo
echo "Generating Unix makefile"
echo "------------------------"

generate_unix_makefiles "Debug"
generate_unix_makefiles "Release"
generate_unix_makefiles "RelWithDebInfo"
generate_unix_makefiles "MinSizeRel"

# Back to the directory where the script was started from
cd $EXECUTION_DIR