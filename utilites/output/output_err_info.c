#include "../../include/output_err_info.h"

void print_err_OK() {
    printf("End of program work.\nIf errors occur or you have any suggestions, you can write an issue: https://github.com/Larionov-VA/raster_meta/issues\n");
}

void print_err_count(error_info_t* err) {
    printf("Number of errors: %d\n", err->count_of_errors);
}

void print_err_MEM(error_info_t* err) {
    print_err_count(err);
    printf("Last error in execution.\nOut of memory in module: %s\nError code: %d\n", err->location, err->error_state);
}

void print_err_NOARGS(error_info_t* err) {
    print_err_count(err);
    printf("Last error in execution.\nNot enough arguments to execute function in module: %s\nError code: %d\n", err->location, err->error_state);
}

void print_err_EXTRAARGS(error_info_t* err) {
    print_err_count(err);
    printf("Last error in execution.\nExtra arguments for executing a function in a module: %s\nError code: %d\n", err->location, err->error_state);
}

void print_err_FILE(error_info_t* err) {
    print_err_count(err);
    printf("Last error in execution.\nProblems with the file, possibly corrupted or used by another process, which caused an error in the module: %s\nError code: %d\n", err->location, err->error_state);
}

void print_err_LIBPNG(error_info_t* err) {
    print_err_count(err);
    printf("Last error in execution.\nProblems with the file, An error occurred in the libpng library, possibly a problem with the file: %s\nError code: %d\n", err->location, err->error_state);
}

void print_err_INCORRECT_ARG(error_info_t* err) {
    print_err_count(err);
    printf("Last error in execution.\nThe arguments passed are invalid, the program cannot continue. Error location: %s\nError code: %d\n", err->location, err->error_state);
}

void print_err_UNKNOWNERR(error_info_t* err) {
    printf("Unknown error: %d. Location: %s\n", err->error_state, err->location);
}