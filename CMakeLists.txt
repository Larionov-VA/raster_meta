cmake_minimum_required(VERSION 3.14)
project(raster_meta)

include(FetchContent)

find_package(PNG QUIET)

if(NOT PNG_FOUND)
    message(STATUS "libpng not found. Downloading and building from source...")

    FetchContent_Declare(
        libpng
        URL https://download.sourceforge.net/libpng/libpng-1.6.43.tar.gz
        URL_HASH SHA256=6a57d9e3ffd8f7d7f2855b5b8770fbea720a4c0a6d4e1e8e6c256f7d799bd5a5
    )

    FetchContent_MakeAvailable(libpng)

    set(PNG_LIBRARY png)
    set(PNG_INCLUDE_DIR ${libpng_SOURCE_DIR} ${libpng_BINARY_DIR})
endif()

set(SOURCE_LIB
    main.c
    utilites/init_stuctures.c
    utilites/parsers/argsparser.c
    utilites/parsers/fileparser.c
    utilites/parsers/PNGparser.c
    utilites/err.c
    utilites/output/output_info.c
    utilites/output/output_PNG_info.c
    utilites/output/output_BMP_info.c
)

add_executable(main ${SOURCE_LIB})
target_include_directories(main PRIVATE ${PNG_INCLUDE_DIR})
target_link_libraries(main PRIVATE ${PNG_LIBRARY})
