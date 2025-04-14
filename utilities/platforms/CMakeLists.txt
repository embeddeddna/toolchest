cmake_minimum_required(VERSION 3.10)
project(ministorm C)

set(CMAKE_C_STANDARD 99)

# Define source path if not set
if(NOT DEFINED SRC_PATH)
  set(SRC_PATH "${CMAKE_SOURCE_DIR}/../src")
endif()

# Define include path
set(INCLUDE_PATH "${CMAKE_SOURCE_DIR}/../include")
include_directories(${INCLUDE_PATH})

# Source files
set(src_files 
        "${SRC_PATH}/linkedListDynamic.c"
        "${SRC_PATH}/logger.c")

# Create the static library
add_library(embdnautilities STATIC ${src_files})

# Specify include files for installation
install(DIRECTORY ${INCLUDE_PATH}/
        DESTINATION include/embdna
        FILES_MATCHING PATTERN "*.h")

# Install the static library
install(TARGETS embdnautilities
        ARCHIVE DESTINATION lib)
