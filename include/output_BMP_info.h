#include "./structures.h"
#include <stdio.h>

void print_all_BMP_info(file_meta_t* file_info);
void print_BMP_file_format(int bmp_format);
void print_BMP_resolution(file_meta_t* file_info);
void print_BMP_size(file_meta_t* file_info);
void print_BMP_bitdepth(file_meta_t* file_info);
void print_BMP_planes(file_meta_t* file_info);
void print_BMP_compression(file_meta_t* file_info);
void print_BMP_PPM(file_meta_t* file_info);
void print_BMP_color_in_color_table(file_meta_t* file_info);
void print_BMP_important_color_count(file_meta_t* file_info);
void print_BMP_color_bitmasks(file_meta_t* file_info);
void print_BMP_color_space_type(file_meta_t* file_info);
void print_BMP_color_endpoints(file_meta_t* file_info);
void print_BMP_gamma_for_channels(file_meta_t* file_info);
void print_BMP_intent(file_meta_t* file_info);
void print_BMP_ICC_profile_data(file_meta_t* file_info);
void print_BMP_ICC_profile_size(file_meta_t* file_info);