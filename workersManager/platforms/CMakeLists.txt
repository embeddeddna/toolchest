cmake_minimum_required(VERSION 3.10)
project(ministorm C)

set(CMAKE_C_STANDARD 99)

# first check
if(NOT DEFINED SRC_PATH)
  SET(SRC_PATH "../src")
endif(NOT DEFINED SRC_PATH)

# Define include path
set(INCLUDE_PATH "${CMAKE_SOURCE_DIR}/../include")
include_directories(${INCLUDE_PATH})

SET(src_files "${SRC_PATH}/worker.c"
"${SRC_PATH}/workerManager.c")

# Create the static library
add_library(workersManager STATIC ${src_files})

# Specify include files for installation
install(DIRECTORY ${INCLUDE_PATH}/
        DESTINATION include
        FILES_MATCHING PATTERN "*.h")

# Install the static library
install(TARGETS workersManager
        ARCHIVE DESTINATION lib)