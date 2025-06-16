#include "../include/err.h"

void set_err(error_info_t* err, int state, char* err_location) {
    err->error_state = state;
    ++err->count_of_errors;
    strcpy(err->location, err_location);
}