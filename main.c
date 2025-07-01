#include "./include/structures.h"
#include "./include/init_structures.h"
#include "./include/argsparser.h"
#include "./include/fileparser.h"
#include "./include/output_info.h"

int main(int argc, char* argv[]) {
    error_info_t err_struct = get_clear_error_struct();
    options_t opt = get_clear_options_struct();
    parse_args(argc, argv, &err_struct, &opt);
    if (!err_struct.count_of_errors) {
        file_meta_t file_info;
        get_file_info(&opt, &err_struct, &file_info);
        if (!err_struct.count_of_errors) {
            print_file_info(&file_info);
        }
    }
    print_error_info(&err_struct);
    return err_struct.error_state;
}