#include "./structures.h"
#include <stdio.h>

void print_err_OK();
void print_err_count(error_info_t* err);
void print_err_MEM(error_info_t* err);
void print_err_NOARGS(error_info_t* err);
void print_err_EXTRAARGS(error_info_t* err);
void print_err_FILE(error_info_t* err);
void print_err_INCORRECT_ARG(error_info_t* err);
void print_err_UNKNOWNERR(error_info_t* err);