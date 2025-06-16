#include "../include/structures.h"
#include "../include/err.h"
#include <png.h>
#define ERROR_LOCATION_FILEPARSER "file: fileparser.c"
#define PNG_SIG_LENGTH 8
#define BMP_SIG_LENGTH 2
void get_file_info(options_t* opt, error_info_t* err, file_meta_t* meta);