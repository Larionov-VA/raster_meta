#include "../../include/output_info.h"
#include "../../include/output_PNG_info.h"
#include "../../include/output_BMP_info.h"

void print_file_info(file_meta_t* file_info) {
    switch (file_info->format) {
    case PNG:
        print_all_PNG_info(file_info);
        break;
    case BMP:
        print_all_BMP_info(file_info);
        break;
    default:
        printf("File format: UNKNOWN\n");
        break;
    }
}