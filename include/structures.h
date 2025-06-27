#pragma once
#include <png.h>

#define MAX_FILENAME_LENGTH 255

/*BMP version*/
#define BITMAPCOREHEADER 12
#define BITMAPINFOHEADER 40
#define BITMAPV2INFOHEADER 52
#define BITMAPV3INFOHEADER 56
#define BITMAPV4HEADER 108
#define BITMAPV5HEADER 124

/*BMP intent type*/
#define LCS_GM_BUSINESS 1
#define LCS_GM_GRAPHICS 2
#define LCS_GM_IMAGES 4
#define LCS_GM_ABS_COLORIMETRIC	8

/*BMP color profile (color space type)*/
#define SRGB 0x73524742
#define WIN 0x57696E20
#define LINK 0x4C494E4B
#define MBED 0x4D424544

/*BMP compression type*/
#define BI_RGB 0
#define BI_RLE8 1
#define BI_RLE4 2
#define BI_BITFIELDS 3
#define BI_JPEG 4
#define BI_PNG 5
#define BI_ALPHABITFIELDS 6

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

typedef enum {
    ERR_OK,
    ERR_MEM,
    ERR_NOARGS,
    ERR_EXTRAARGS,
    ERR_DIR,
    ERR_FILE,
    ERR_INCORRECT_ARG
} error_t;

typedef struct {
    error_t error_state;
    char location[MAX_FILENAME_LENGTH];
    int count_of_errors;
} error_info_t;

typedef struct {
    char input_filename[MAX_FILENAME_LENGTH];
} options_t;

#pragma pack (push, 2)
typedef struct {
    unsigned short signature;
    unsigned int filesize;
    unsigned short reserved1;
    unsigned short reserved2;
    unsigned int pixel_arr_offset;
} BMP_file_header_t;

typedef struct {
    unsigned int ciexyzX;
    unsigned int ciexyzY;
    unsigned int ciexyzZ;
} BMP_ciexyz_t;

typedef struct {
    BMP_ciexyz_t Red;
    BMP_ciexyz_t Green;
    BMP_ciexyz_t Blue;
} BMP_endpoints_t;

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

    unsigned int red_channel_bitmask;
    unsigned int green_channel_bitmask;
    unsigned int blue_channel_bitmask;

    unsigned int alpha_channel_bitmask;

    unsigned int color_space_type;
    BMP_endpoints_t color_space_endpoints;
    unsigned int gamma_for_red_channel;
    unsigned int gamma_for_green_channel;
    unsigned int gamma_for_blue_channel;

    unsigned int intent;
    unsigned int ICC_profile_data;
    unsigned int ICC_profile_size;
    unsigned int reserved;
} BMP_info_header_t;

typedef struct {
	BMP_file_header_t file_header;
	BMP_info_header_t info_header;
} BMP_info_struct_t;
#pragma pack (pop)

typedef struct {
    // tEXt chunk
    png_textp text_chunks;
    int num_text_chunks;
    // tIME chunk
    png_time time_chunk;
    int has_time_chunk;
    // gAMA chunk
    double gamma;
    int has_gama;
    // cHRM chunk
    double white_x, white_y;
    double red_x, red_y;
    double green_x, green_y;
    double blue_x, blue_y;
    int has_chrm;
    // sRGB chunk
    int srgb_intent;
    int has_srgb;
    // iCCP chunk
    char* iccp_name;
    png_bytep iccp_profile;
    png_uint_32 iccp_proflen;
    int iccp_compression;
    int has_iccp;
    // sBIT chunk
    png_color_8 sbit;
    int has_sbit;
    // hIST chunk
    png_uint_16p hist;
    int num_hist_entries;
    int has_hist;
    // pHYs chunk
    png_uint_32 phys_x, phys_y;
    int phys_unit_type;
    int has_phys; 
    // bKGD chunk 
    png_color_16 bkgd;
    int has_bkgd;
    // tRNS chunk
    png_bytep trans_alpha;
    int num_trans;
    png_color_16 trans_color;
    int has_trns;
    // eXIf chunk
    png_bytep exif;
    png_uint_32 exif_length;
    int has_exif;
    // sPLT chunks
    png_sPLT_tp splt_chunks;
    int num_splt_chunks;
} png_chunks_info;

typedef struct {
    unsigned width;
    unsigned height;
    int color_type;
    int bit_depth;
    unsigned compression_type;
    int interlace_type;
    unsigned filter_method;
    png_chunks_info chunks;
} PNG_info_struct_t;

typedef struct {
    file_format_t format;
    BMP_info_struct_t bmp_info;
    PNG_info_struct_t png_info;
} file_meta_t;