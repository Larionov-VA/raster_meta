#pragma once
#define MAX_FILENAME_SIZE 255

typedef enum {
    ERR_OK,
    ERR_MEM,
    ERR_NOARGS,
    ERR_EXTRAARGS,
    ERR_DIR,
    ERR_FILE,
    ERR_INCORRECT_ARG
} error_t;

typedef struct {
    error_t error_state;
    char location[MAX_FILENAME_SIZE];
    int count_of_errors;
} error_info_t;

typedef struct {
    char input_filename[MAX_FILENAME_SIZE];
} options_t;

