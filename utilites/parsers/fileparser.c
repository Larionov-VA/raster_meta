#include "../../include/fileparser.h"

void get_file_info(options_t* opt, error_info_t* err, file_meta_t* meta) {
    FILE* file = fopen(opt->input_filename, "rb");
    if (file) {
        meta->format = get_file_format(file);
        switch (meta->format) {
        case PNG:
            get_info_about_PNG(meta, err, file);
            break;
        case BMP:
            get_info_about_BMP(meta, err, file);
            break;
        case UNKNOWN:
            set_err(err, ERR_FILE, ERROR_LOCATION_FILEPARSER);
            break;
        }
        fclose(file);
    }
    else {
        set_err(err, ERR_FILE, ERROR_LOCATION_FILEPARSER);
    }
}

file_format_t get_file_format(FILE* file) {
    file_format_t format = UNKNOWN;
    char png_header[PNG_SIG_LENGTH];
    char bmp_header[BMP_SIG_LENGTH];
    if (fread(png_header, 1, PNG_SIG_LENGTH, file) == PNG_SIG_LENGTH) {
        if (png_sig_cmp(png_header, 0, 8) == 0) {
            format = PNG;
        }
    }
    if (!format) {
        rewind(file);
    }
    if (!format && fread(bmp_header, 1, BMP_SIG_LENGTH, file) == BMP_SIG_LENGTH) {
        if (!memcmp(bmp_header, "BM", 2)) {
            format = BMP;
        }
    }
    return format;
}

void get_info_about_PNG(file_meta_t* meta, error_info_t* err, FILE* file) {
    png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);;
    png_infop info_ptr = png_create_info_struct(png_ptr);
    if (init_png_reading(&png_ptr, &info_ptr, file, err)) {
        skip_pixel_data(png_ptr, info_ptr);
        read_IHDR(png_ptr, info_ptr, meta);
        read_text_chunks(png_ptr, info_ptr, meta, err);
        read_time_chunk(png_ptr, info_ptr, meta);
        read_gama_chunk(png_ptr, info_ptr, meta);
        read_chrm_chunk(png_ptr, info_ptr, meta);
        read_srgb_chunk(png_ptr, info_ptr, meta);
        read_iccp_chunk(png_ptr, info_ptr, meta, err);
        read_sbit_chunk(png_ptr, info_ptr, meta);
        read_hist_chunk(png_ptr, info_ptr, meta, err);
        read_phys_chunk(png_ptr, info_ptr, meta);
        read_bkgd_chunk(png_ptr, info_ptr, meta);
        read_trns_chunk(png_ptr, info_ptr, meta);
        read_exif_chunk(png_ptr, info_ptr, meta, err);
        read_splt_chunks(png_ptr, info_ptr, meta, err);
        png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
    }
}

void get_info_about_BMP(file_meta_t* meta, error_info_t* err, FILE* file){
    rewind(file);
    fread(&meta->bmp_info.file_header, 1, sizeof(BMP_file_header_t), file);
	fread(&meta->bmp_info.info_header, 1, sizeof(BMP_info_header_t), file);
}