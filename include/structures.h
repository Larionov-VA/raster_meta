#pragma once
#define MAX_FILENAME_LENGTH 255
#define MAX_FORMAT_LENGTH 15

typedef enum {
    ERR_OK,
    ERR_MEM,
    ERR_NOARGS,
    ERR_EXTRAARGS,
    ERR_DIR,
    ERR_FILE,
    ERR_INCORRECT_ARG
} error_t;

typedef enum {
    UNKNOWN,
    PNG,
    BMP,
} file_format_t;

typedef struct {
    error_t error_state;
    char location[MAX_FILENAME_LENGTH];
    int count_of_errors;
} error_info_t;

typedef struct {
    char input_filename[MAX_FILENAME_LENGTH];
} options_t;

typedef struct {
    file_format_t format;
    char format_version[MAX_FORMAT_LENGTH];
} file_meta_t;
