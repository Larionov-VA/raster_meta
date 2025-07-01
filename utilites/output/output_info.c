#include "../../include/output_info.h"
#include "../../include/output_PNG_info.h"
#include "../../include/output_BMP_info.h"
#include "../../include/output_err_info.h"

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

void print_error_info(error_info_t* err) {
    switch (err->error_state) {
    case ERR_OK:
        print_err_OK();
        break;
    case ERR_MEM:
        print_err_MEM(err);
        break;
    case ERR_NOARGS:
        print_err_NOARGS(err);
        break;
    case ERR_EXTRAARGS:
        print_err_EXTRAARGS(err);
        break;
    case ERR_FILE:
        print_err_FILE(err);
        break;
    case ERR_INCORRECT_ARG:
        print_err_INCORRECT_ARG(err);
        break;
    default:
        print_err_UNKNOWNERR(err);
        break;
    }
}