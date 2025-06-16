#include "./include/structures.h"
#include "./include/init_structures.h"
#include "./include/get_options.h"

int main(int argc, char* argv[]) {
    error_info_t err_struct = get_clear_error_struct();
    options_t opt = get_clear_options_struct();
    parse_args(argc, argv, &err_struct, &opt);
    if (!err_struct.count_of_errors) {
        // read_file_info(optionts, &err);
    }
    return err_struct.error_state;
}