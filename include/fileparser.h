#include "../include/structures.h"
#include "../include/err.h"
#include "../include/PNGparser.h"
#include <png.h>
#include <stdlib.h>
#define ERROR_LOCATION_FILEPARSER "file: fileparser.c"
#define BMP_SIG_LENGTH 2
#define PNG_SIG_LENGTH 8

void get_info_about_PNG(file_meta_t* meta, error_info_t* err, FILE* file);
void get_info_about_BMP(file_meta_t* meta, error_info_t* err, FILE* file);
file_format_t get_file_format(FILE* file);
void get_file_info(options_t* opt, error_info_t* err, file_meta_t* meta);