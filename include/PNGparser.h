#include "../include/structures.h"
#include "../include/err.h"
#include <png.h>
#include <stdlib.h>
#define ERROR_LOCATION_PNGPARSER "file: PNGparser.c"
#define PNG_SIG_LENGTH 8

int init_png_reading(png_structp* png_ptr_out, png_infop* info_ptr_out, FILE* file, error_info_t* err);
void skip_pixel_data(png_structp png_ptr, png_infop info_ptr);
void read_IHDR(png_structp png_ptr, png_infop info_ptr, file_meta_t* meta);
void read_text_chunks(png_structp png_ptr, png_infop info_ptr, file_meta_t* meta, error_info_t* err);
void read_time_chunk(png_structp png_ptr, png_infop info_ptr, file_meta_t* meta);
void read_gama_chunk(png_structp png_ptr, png_infop info_ptr, file_meta_t* meta);
void read_chrm_chunk(png_structp png_ptr, png_infop info_ptr, file_meta_t* meta);
void read_srgb_chunk(png_structp png_ptr, png_infop info_ptr, file_meta_t* meta);
void read_iccp_chunk(png_structp png_ptr, png_infop info_ptr, file_meta_t* meta, error_info_t* err);
void read_sbit_chunk(png_structp png_ptr, png_infop info_ptr, file_meta_t* meta);
void read_hist_chunk(png_structp png_ptr, png_infop info_ptr, file_meta_t* meta, error_info_t* err);
void read_phys_chunk(png_structp png_ptr, png_infop info_ptr, file_meta_t* meta);
void read_bkgd_chunk(png_structp png_ptr, png_infop info_ptr, file_meta_t* meta);
void read_trns_chunk(png_structp png_ptr, png_infop info_ptr, file_meta_t* meta);
void read_exif_chunk(png_structp png_ptr, png_infop info_ptr, file_meta_t* meta, error_info_t* err);
void read_splt_chunks(png_structp png_ptr, png_infop info_ptr, file_meta_t* meta, error_info_t* err);