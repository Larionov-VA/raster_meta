cmake_minimum_required(VERSION 3.0)
project(raster_meta)

set(SOURCE_EXE main.c)
set(SOURCE_LIB utilites/init_stuctures.c CLI/get_options.c)

add_library(init_stuctures STATIC ${SOURCE_LIB})
add_executable(main ${SOURCE_EXE})
target_link_libraries(main init_stuctures)