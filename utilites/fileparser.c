#include "../include/fileparser.h"

file_format_t get_file_format(FILE* file) {
    file_format_t format = UNKNOWN;
    char png_header[PNG_SIG_LENGTH];
    char bmp_header[BMP_SIG_LENGTH];
    if (fread(png_header, 1, PNG_SIG_LENGTH, file) == PNG_SIG_LENGTH) {
        if (png_sig_cmp(png_header, 0, 8) == 0) {
            format = PNG;
        }
    }
    rewind(file);
    if (!format && fread(bmp_header, 1, BMP_SIG_LENGTH, file) == BMP_SIG_LENGTH) {
        if (!memcmp(bmp_header, "BM", 2)) {
            format = BMP;
        }
    }
    rewind(file);
    return format;
}

void get_file_info(options_t* opt, error_info_t* err, file_meta_t* meta) {
    printf("parse\n");
    FILE* file = fopen(opt->input_filename, "rb");
    if (file) {
        file_format_t format = get_file_format(file);
        switch (format) {
        case UNKNOWN:
            set_err(err, ERR_FILE, ERROR_LOCATION_FILEPARSER);
            break;
        case PNG:

            break;
        case BMP:

            break;
        }
    }
    else {
        set_err(err, ERR_MEM, ERROR_LOCATION_FILEPARSER);
    }
}