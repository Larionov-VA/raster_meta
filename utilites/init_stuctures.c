#include "../include/init_structures.h"

error_info_t get_clear_error_struct() {
    error_info_t error;
    error.count_of_errors = 0;
    error.error_state = ERR_OK;
    return error;
}

options_t get_clear_options_struct() {
    options_t opt;
    opt.input_filename[0] = '\0';
    return opt;
}