#include "../include/argsparser.h"

void parse_args(int argc, char* argv[], error_info_t* err, options_t* options) {
    int opt, longIndex;
    char *opts = "i:?";
    struct option longOpts[] = {
        {"input", required_argument, NULL, SHORTOPT_INPUT},
        {NULL, 0, NULL, 0}
    };
    opt = getopt_long(argc, argv, opts, longOpts, &longIndex);
    while (opt != -1 && !err->error_state) {
        switch (opt) {
        case SHORTOPT_INPUT:
            if (!strcmp(options->input_filename, "")) {
                strcpy(options->input_filename, optarg);
            }
            else {
                set_err(err, ERR_FILE, ERROR_LOCATION_ARGPARSER);
            }
            break;
        case SHORTOPT_INCORRECT_FLAG:
            set_err(err, ERR_FILE, ERROR_LOCATION_ARGPARSER);
            break;
        }
        opt = getopt_long(argc, argv, opts, longOpts, &longIndex);
    }
    argc -= optind; argv += optind;
    if (argc) {
        if (argc == 1 && !strcmp(options->input_filename, "")) {
            strcpy(options->input_filename, argv[0]);
        } else {
            set_err(err, ERR_FILE, ERROR_LOCATION_ARGPARSER);
        }
    }
}