#include "../include/fileparser.h"

void get_info_about_PNG(file_meta_t* meta, error_info_t* err, FILE* file) {
    png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    png_infop info_ptr = png_create_info_struct(png_ptr);
    png_init_io(png_ptr, file);
    png_set_sig_bytes(png_ptr, PNG_SIG_LENGTH);
    png_read_info(png_ptr, info_ptr);
    
    png_uint_32 height = png_get_image_height(png_ptr, info_ptr);
    for (png_uint_32 row = 0; row < height; row++) {
        png_read_row(png_ptr, NULL, NULL);
    }
    png_read_end(png_ptr, info_ptr);

    png_get_IHDR(png_ptr, info_ptr, &meta->png_info.width, &meta->png_info.height,
        &meta->png_info.bit_depth, &meta->png_info.color_type, &meta->png_info.interlace_type,
        &meta->png_info.compression_type, &meta->png_info.filter_method);

    png_textp text_ptr = NULL;
    int num_text = png_get_text(png_ptr, info_ptr, &text_ptr, NULL);
    meta->png_info.chunks.num_text_chunks = num_text;
    meta->png_info.chunks.text_chunks = NULL;

    if (num_text > 0) {
        meta->png_info.chunks.text_chunks = malloc(num_text * sizeof(png_text));
        if (meta->png_info.chunks.text_chunks) {
            for (int i = 0; i < num_text; i++) {
                meta->png_info.chunks.text_chunks[i].key = strdup(text_ptr[i].key);
                meta->png_info.chunks.text_chunks[i].text = strdup(text_ptr[i].text ? text_ptr[i].text : "");
                meta->png_info.chunks.text_chunks[i].compression = text_ptr[i].compression;
            }
        } else {
            set_err(err, ERR_MEM, ERROR_LOCATION_FILEPARSER);
        }
    }

    png_timep time_ptr;
    if (png_get_tIME(png_ptr, info_ptr, &time_ptr)) {
        meta->png_info.chunks.has_time_chunk = 1;
        meta->png_info.chunks.time_chunk = *time_ptr;
    } else {
        meta->png_info.chunks.has_time_chunk = 0;
    }

    if (png_get_gAMA(png_ptr, info_ptr, &meta->png_info.chunks.gamma)) {
        meta->png_info.chunks.has_gama = 1;
    } else {
        meta->png_info.chunks.has_gama = 0;
    }
 
    if (png_get_cHRM(png_ptr, info_ptr,
        &meta->png_info.chunks.white_x, &meta->png_info.chunks.white_y,
        &meta->png_info.chunks.red_x, &meta->png_info.chunks.red_y,
        &meta->png_info.chunks.green_x, &meta->png_info.chunks.green_y,
        &meta->png_info.chunks.blue_x, &meta->png_info.chunks.blue_y)) 
    {
        meta->png_info.chunks.has_chrm = 1;
    } else {
        meta->png_info.chunks.has_chrm = 0;
    }

    if (png_get_sRGB(png_ptr, info_ptr, &meta->png_info.chunks.srgb_intent)) {
        meta->png_info.chunks.has_srgb = 1;
    } else {
        meta->png_info.chunks.has_srgb = 0;
    }

    png_charp iccp_name;
    png_bytep iccp_profile;
    png_uint_32 iccp_proflen;
    int iccp_compression;
    if (png_get_iCCP(png_ptr, info_ptr, &iccp_name, &iccp_compression, &iccp_profile, &iccp_proflen)) {
        meta->png_info.chunks.has_iccp = 1;
        meta->png_info.chunks.iccp_name = strdup(iccp_name);
        meta->png_info.chunks.iccp_compression = iccp_compression;
        meta->png_info.chunks.iccp_profile = malloc(iccp_proflen);
        if (meta->png_info.chunks.iccp_profile) {
            memcpy(meta->png_info.chunks.iccp_profile, iccp_profile, iccp_proflen);
        }
        meta->png_info.chunks.iccp_proflen = iccp_proflen;
    } else {
        meta->png_info.chunks.has_iccp = 0;
    }

    png_color_8p sig_bit;
    if (png_get_sBIT(png_ptr, info_ptr, &sig_bit)) {
        meta->png_info.chunks.has_sbit = 1;
        meta->png_info.chunks.sbit = *sig_bit;
    } else {
        meta->png_info.chunks.has_sbit = 0;
    }


    png_uint_16p hist_ptr = NULL;
    if (png_get_hIST(png_ptr, info_ptr, &hist_ptr)) {
        meta->png_info.chunks.has_hist = 1;
        png_uint_32 num_entries = png_get_PLTE(png_ptr, info_ptr, NULL, NULL);
        meta->png_info.chunks.num_hist_entries = num_entries;
        meta->png_info.chunks.hist = malloc(num_entries * sizeof(png_uint_16));
        if (meta->png_info.chunks.hist) {
            memcpy(meta->png_info.chunks.hist, hist_ptr, num_entries * sizeof(png_uint_16));
        } else { 
            set_err(err, ERR_MEM, ERROR_LOCATION_FILEPARSER); 
        }
    } else {
        meta->png_info.chunks.has_hist = 0;
    }

    if (png_get_pHYs(png_ptr, info_ptr,
        &meta->png_info.chunks.phys_x, &meta->png_info.chunks.phys_y,
        &meta->png_info.chunks.phys_unit_type)) 
    {
        meta->png_info.chunks.has_phys = 1;
    } else {
        meta->png_info.chunks.has_phys = 0;
    }

    png_color_16p background;
    if (png_get_bKGD(png_ptr, info_ptr, &background)) {
        meta->png_info.chunks.has_bkgd = 1;
        meta->png_info.chunks.bkgd = *background;
    } else {
        meta->png_info.chunks.has_bkgd = 0;
    }

    png_bytep trans;
    int num_trans;
    png_color_16p trans_values;
    if (png_get_tRNS(png_ptr, info_ptr, &trans, &num_trans, &trans_values)) {
        meta->png_info.chunks.has_trns = 1;
        meta->png_info.chunks.trans_alpha = trans;
        meta->png_info.chunks.num_trans = num_trans;
        if (trans_values) {
            meta->png_info.chunks.trans_color = *trans_values;
        }
    } else {
        meta->png_info.chunks.has_trns = 0;
    }

    png_bytep exif;
    png_uint_32 exif_length;
    if (png_get_eXIf_1(png_ptr, info_ptr, &exif_length, &exif)) {
        meta->png_info.chunks.has_exif = 1;
        meta->png_info.chunks.exif = malloc(exif_length);
        if (meta->png_info.chunks.exif) {
            memcpy(meta->png_info.chunks.exif, exif, exif_length);
        }
        meta->png_info.chunks.exif_length = exif_length;
    } else {
        meta->png_info.chunks.has_exif = 0;
    }

    png_sPLT_tp splt_ptr;
    int num_splt = png_get_sPLT(png_ptr, info_ptr, &splt_ptr);
    meta->png_info.chunks.num_splt_chunks = num_splt;
    meta->png_info.chunks.splt_chunks = NULL;

    if (num_splt > 0) {
        meta->png_info.chunks.splt_chunks = malloc(num_splt * sizeof(png_sPLT_t));
        if (meta->png_info.chunks.splt_chunks) {
            for (int i = 0; i < num_splt; i++) {
                meta->png_info.chunks.splt_chunks[i].name = strdup(splt_ptr[i].name);
                meta->png_info.chunks.splt_chunks[i].depth = splt_ptr[i].depth;
                meta->png_info.chunks.splt_chunks[i].entries = malloc(splt_ptr[i].nentries * sizeof(png_sPLT_entry));
                if (meta->png_info.chunks.splt_chunks[i].entries) {
                    memcpy(meta->png_info.chunks.splt_chunks[i].entries,
                           splt_ptr[i].entries,
                           splt_ptr[i].nentries * sizeof(png_sPLT_entry));
                }
                meta->png_info.chunks.splt_chunks[i].nentries = splt_ptr[i].nentries;
            }
        } else {
            set_err(err, ERR_MEM, ERROR_LOCATION_FILEPARSER);
        }
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