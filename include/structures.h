#pragma once
#define MAX_FILENAME_LENGTH 255
#include <png.h>

typedef enum {
    ERR_OK,
    ERR_MEM,
    ERR_NOARGS,
    ERR_EXTRAARGS,
    ERR_DIR,
    ERR_FILE,
    ERR_INCORRECT_ARG
} error_t;

typedef enum {
    UNKNOWN,
    PNG,
    BMP,
} file_format_t;

typedef enum {
    GRAY_OR_PALETTE = 1,
    GRAY_ALPHA,
    RGB,
    RGB_ALPHA
} color_type_t;

typedef struct {
    error_t error_state;
    char location[MAX_FILENAME_LENGTH];
    int count_of_errors;
} error_info_t;

typedef struct {
    char input_filename[MAX_FILENAME_LENGTH];
} options_t;

#pragma pack (push, 1)
typedef struct {
	unsigned short signature;
	unsigned int filesize;
	unsigned short reserved1;
	unsigned short reserved2;
	unsigned int pixel_arr_offset;
} BMP_file_header_t;

typedef struct {
	unsigned int header_size;
	unsigned int width;
	unsigned int height;
	unsigned short planes;
	unsigned short bits_per_pixel;
	unsigned int compression;
	unsigned int image_size;
	unsigned int x_PPM;
	unsigned int y_PPM;
	unsigned int colors_in_color_table;
	unsigned int important_color_count;
} BMP_info_header_t;

typedef struct {
	BMP_file_header_t file_header;
	BMP_info_header_t info_header;
} BMP_info_struct_t;

#pragma pack (pop)

typedef struct {
    unsigned width;
    unsigned height;
    int color_type;
    int bit_depth;
    png_byte channels;
    unsigned compression_type;
    int interlace_type;
    unsigned filter_method;
} PNG_info_struct_t;

typedef struct {
    file_format_t format;
    BMP_info_struct_t bmp_info;
    PNG_info_struct_t png_info;
} file_meta_t;