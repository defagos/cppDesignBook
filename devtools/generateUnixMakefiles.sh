#!/bin/bash

# Directory containing this file (absolute)
SCRIPT_FILE_DIR=`dirname $0`
SCRIPT_FILE_DIR=`cd $SCRIPT_FILE_DIR; pwd`

$SCRIPT_FILE_DIR/common/generator.sh UnixMakefiles $SCRIPT_FILE_DIR/.. $SCRIPT_FILE_DIR