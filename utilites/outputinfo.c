#include "../include/outputinfo.h"


void print_file_info(file_meta_t* file_info) {
    switch (file_info->format) {
    case PNG:
        printf("File format: PNG\n");
        printf("Frequence: width %d height %d\n",\
        file_info->png_info.width, file_info->png_info.height);
        switch (file_info->png_info.color_type) {
        case PNG_COLOR_TYPE_GRAY:
            printf("Color type: GRAY\n");
            break;
        case PNG_COLOR_TYPE_PALETTE:
            printf("Color type: PALETTE\n");
            break;
        case PNG_COLOR_TYPE_RGB:
            printf("Color type: RGB\n");
            break;
        case PNG_COLOR_TYPE_RGBA:
            printf("Color type: RGBA\n");
            break;
        case PNG_COLOR_TYPE_GA:
            printf("Color type: GA\n");
            break;
        default:
            printf("Color type: %d\n", file_info->png_info.color_type);
        }
        printf("Bit depth: %u\nChannels: %u\n",\
        file_info->png_info.bit_depth, file_info->png_info.channels);
        break;
    case BMP:
        printf("File format: BMP\n");
        printf("Frequence: width %d height %d\n",\
        file_info->bmp_info.info_header.width, file_info->bmp_info.info_header.height);
        break;
    default:
        printf("File format: UNKNOWN\n");
        break;
    }
}
