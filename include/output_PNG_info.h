#include "./structures.h"
#include <stdio.h>

void print_all_PNG_info(file_meta_t* file_info);
void print_PNG_file_format();
void print_PNG_resolution(file_meta_t* file_info);
void print_PNG_colortype(file_meta_t* file_info);
void print_PNG_bitdepth(file_meta_t* file_info);
void print_PNG_tEXt_chunk(file_meta_t* file_info);
void print_PNG_tIME_chunk(file_meta_t* file_info);
void print_PNG_gAMA_chunk(file_meta_t* file_info);
void print_PNG_cHRM_chunk(file_meta_t* file_info);
void print_PNG_sRGB_chunk(file_meta_t* file_info);
void print_PNG_iCCP_chunk(file_meta_t* file_info);
void print_PNG_sBIT_chunk(file_meta_t* file_info);
void print_PNG_hIST_chunk(file_meta_t* file_info);
void print_PNG_pHYs_chunk(file_meta_t* file_info);
void print_PNG_bKGD_chunk(file_meta_t* file_info);
void print_PNG_tRNS_chunk(file_meta_t* file_info);
void print_PNG_eXIf_chunk(file_meta_t* file_info);
void print_PNG_sPLT_chunk(file_meta_t* file_info);