#include "../include/fileparser.h"

void get_info_about_PNG(file_meta_t* meta, error_info_t* err, FILE* file){
    png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    png_infop info_ptr = png_create_info_struct(png_ptr);
    png_init_io(png_ptr, file);
    png_set_sig_bytes(png_ptr, PNG_SIG_LENGTH);
    png_read_info(png_ptr, info_ptr);
    png_get_IHDR(png_ptr, info_ptr, &meta->png_info.width, &meta->png_info.height,\
    &meta->png_info.bit_depth, &meta->png_info.color_type, &meta->png_info.interlace_type,\
    &meta->png_info.compression_type, &meta->png_info.filter_method);

    png_textp text_ptr = NULL;
    int num_text = png_get_text(png_ptr, info_ptr, &text_ptr, NULL);
    meta->png_info.chunks.num_text_chunks = num_text;
    meta->png_info.chunks.text_chunks = NULL;

    if (num_text > 0) {
        meta->png_info.chunks.text_chunks = malloc(num_text * sizeof(png_textp));
        if (meta->png_info.chunks.text_chunks) {
            for (int i = 0; i < num_text; i++) {
                meta->png_info.chunks.text_chunks[i].key = strdup(text_ptr[i].key);
                meta->png_info.chunks.text_chunks[i].text = strdup(text_ptr[i].text ? text_ptr[i].text : "");
            }
        }
        else {
            set_err(err, ERR_MEM, ERROR_LOCATION_FILEPARSER);
        }
    }
    png_timep time_ptr;
    if (png_get_tIME(png_ptr, info_ptr, &time_ptr)) {
        meta->png_info.chunks.has_time_chunk = 1;
        meta->png_info.chunks.time_chunk = *time_ptr;
    }
    else {
        meta->png_info.chunks.has_time_chunk = 0;
    }
    png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
}

void get_info_about_BMP(file_meta_t* meta, error_info_t* err, FILE* file){
    rewind(file);
    fread(&meta->bmp_info.file_header, 1, sizeof(BMP_file_header_t), file);
	fread(&meta->bmp_info.info_header, 1, sizeof(BMP_info_header_t), file);
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

void get_file_info(options_t* opt, error_info_t* err, file_meta_t* meta) {
    FILE* file = fopen(opt->input_filename, "rb");
    if (file) {
        meta->format = get_file_format(file);
        switch (meta->format) {
        case UNKNOWN:
            set_err(err, ERR_FILE, ERROR_LOCATION_FILEPARSER);
            break;
        case PNG:
            get_info_about_PNG(meta, err, file);
            break;
        case BMP:
            get_info_about_BMP(meta, err, file);
            break;
        }
        fclose(file);
    }
    else {
        set_err(err, ERR_FILE, ERROR_LOCATION_FILEPARSER);
    }
}