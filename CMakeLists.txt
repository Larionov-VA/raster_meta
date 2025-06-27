cmake_minimum_required(VERSION 3.0)
project(raster_meta)

set(SOURCE_LIB main.c utilites/init_stuctures.c utilites/argsparser.c utilites/fileparser.c utilites/err.c utilites/output/output_info.c utilites/output/output_PNG_info.c utilites/output/output_BMP_info.c)

find_package(PNG REQUIRED)
include_directories(${PNG_INCLUDE_DIR})

add_executable(main ${SOURCE_LIB})
target_link_libraries(main ${PNG_LIBRARY})
