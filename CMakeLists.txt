cmake_minimum_required(VERSION 3.0)
project(raster_meta)

set(SOURCE_LIB main.c utilites/init_stuctures.c utilites/argsparser.c utilites/fileparser.c utilites/err.c)

find_package(PNG REQUIRED)
include_directories(${PNG_INCLUDE_DIR})

add_executable(main ${SOURCE_LIB})
target_link_libraries(main ${PNG_LIBRARY})
