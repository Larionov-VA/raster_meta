#include "../../include/PNGparser.h"

int init_png_reading(png_structp* png_ptr_out, png_infop* info_ptr_out, FILE* file, error_info_t* err) {
    int marker = 1;
    if (*png_ptr_out) {
        *info_ptr_out = png_create_info_struct(*png_ptr_out);
        if (*info_ptr_out) {
            png_init_io(*png_ptr_out, file);
            png_set_sig_bytes(*png_ptr_out, PNG_SIG_LENGTH);
            png_read_info(*png_ptr_out, *info_ptr_out);
        }
        else {
            marker = 0;
            png_destroy_read_struct(png_ptr_out, NULL, NULL);
            set_err(err, ERR_FILE, ERROR_LOCATION_PNGPARSER);
        }
    } else {
        marker = 0;
        set_err(err, ERR_FILE, ERROR_LOCATION_PNGPARSER);
    }
    return marker;
}

void skip_pixel_data(png_structp png_ptr, png_infop info_ptr) {
    png_uint_32 height = png_get_image_height(png_ptr, info_ptr);
    for (png_uint_32 row = 0; row < height; row++) {
        png_read_row(png_ptr, NULL, NULL);
    }
    png_read_end(png_ptr, info_ptr);
}

void read_IHDR(png_structp png_ptr, png_infop info_ptr, file_meta_t* meta) {
    png_get_IHDR(png_ptr, info_ptr, &meta->png_info.width, &meta->png_info.height, &meta->png_info.bit_depth, &meta->png_info.color_type, &meta->png_info.interlace_type, &meta->png_info.compression_type, &meta->png_info.filter_method);
}

void read_text_chunks(png_structp png_ptr, png_infop info_ptr, file_meta_t* meta, error_info_t* err) {
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
        }
        else {
            set_err(err, ERR_MEM, ERROR_LOCATION_PNGPARSER);
        }
    }
}

void read_time_chunk(png_structp png_ptr, png_infop info_ptr, file_meta_t* meta) {
    png_timep time_ptr;
    meta->png_info.chunks.has_time_chunk = png_get_tIME(png_ptr, info_ptr, &time_ptr);
    if (meta->png_info.chunks.has_time_chunk) {
        meta->png_info.chunks.time_chunk = *time_ptr;
    }
}

void read_gama_chunk(png_structp png_ptr, png_infop info_ptr, file_meta_t* meta) {
    meta->png_info.chunks.has_gama = png_get_gAMA(png_ptr, info_ptr, &meta->png_info.chunks.gamma);
}

void read_chrm_chunk(png_structp png_ptr, png_infop info_ptr, file_meta_t* meta) {
    meta->png_info.chunks.has_chrm = png_get_cHRM(png_ptr, info_ptr, &meta->png_info.chunks.white_x, &meta->png_info.chunks.white_y, &meta->png_info.chunks.red_x, &meta->png_info.chunks.red_y, &meta->png_info.chunks.green_x, &meta->png_info.chunks.green_y, &meta->png_info.chunks.blue_x, &meta->png_info.chunks.blue_y);
}

void read_srgb_chunk(png_structp png_ptr, png_infop info_ptr, file_meta_t* meta) {
    meta->png_info.chunks.has_srgb = png_get_sRGB(png_ptr, info_ptr, &meta->png_info.chunks.srgb_intent);
}

void read_iccp_chunk(png_structp png_ptr, png_infop info_ptr, file_meta_t* meta, error_info_t* err) {
    png_charp iccp_name;
    png_bytep iccp_profile;
    png_uint_32 iccp_proflen;
    int iccp_compression;
    meta->png_info.chunks.has_iccp = png_get_iCCP(png_ptr, info_ptr, &iccp_name, &iccp_compression, &iccp_profile, &iccp_proflen);
    if (meta->png_info.chunks.has_iccp) {
        meta->png_info.chunks.iccp_name = strdup(iccp_name);
        meta->png_info.chunks.iccp_compression = iccp_compression;
        meta->png_info.chunks.iccp_proflen = iccp_proflen;
        if (iccp_proflen > 0) {
            meta->png_info.chunks.iccp_profile = malloc(iccp_proflen);
            if (meta->png_info.chunks.iccp_profile) {
                memcpy(meta->png_info.chunks.iccp_profile, iccp_profile, iccp_proflen);
            } else {
                set_err(err, ERR_MEM, ERROR_LOCATION_PNGPARSER);
            }
        }
    }
}

void read_sbit_chunk(png_structp png_ptr, png_infop info_ptr, file_meta_t* meta) {
    png_color_8p sig_bit;
    meta->png_info.chunks.has_sbit = png_get_sBIT(png_ptr, info_ptr, &sig_bit);
    if (meta->png_info.chunks.has_sbit) {
        meta->png_info.chunks.sbit = *sig_bit;
    }
}

void read_hist_chunk(png_structp png_ptr, png_infop info_ptr, file_meta_t* meta, error_info_t* err) {
    png_uint_16p hist_ptr = NULL;
    meta->png_info.chunks.has_hist = png_get_hIST(png_ptr, info_ptr, &hist_ptr);
    if (meta->png_info.chunks.has_hist) {
        png_uint_32 num_entries = png_get_PLTE(png_ptr, info_ptr, NULL, NULL);
        meta->png_info.chunks.num_hist_entries = num_entries;
        meta->png_info.chunks.hist = malloc(num_entries * sizeof(png_uint_16));
        if (meta->png_info.chunks.hist) {
            memcpy(meta->png_info.chunks.hist, hist_ptr, num_entries * sizeof(png_uint_16));
        } else {
            set_err(err, ERR_MEM, ERROR_LOCATION_PNGPARSER);
        }
    }
}

void read_phys_chunk(png_structp png_ptr, png_infop info_ptr, file_meta_t* meta) {
    meta->png_info.chunks.has_phys = png_get_pHYs(png_ptr, info_ptr, &meta->png_info.chunks.phys_x, &meta->png_info.chunks.phys_y, &meta->png_info.chunks.phys_unit_type);
}

void read_bkgd_chunk(png_structp png_ptr, png_infop info_ptr, file_meta_t* meta) {
    png_color_16p background;
    meta->png_info.chunks.has_bkgd = png_get_bKGD(png_ptr, info_ptr, &background);
    if (meta->png_info.chunks.has_bkgd) {
        meta->png_info.chunks.bkgd = *background;
    }
}

void read_trns_chunk(png_structp png_ptr, png_infop info_ptr, file_meta_t* meta) {
    png_bytep trans;
    int num_trans;
    png_color_16p trans_values;
    meta->png_info.chunks.has_trns = png_get_tRNS(png_ptr, info_ptr, &trans, &num_trans, &trans_values);
    if (meta->png_info.chunks.has_trns) {
        meta->png_info.chunks.trans_alpha = trans;
        meta->png_info.chunks.num_trans = num_trans;
        if (trans_values) {
            meta->png_info.chunks.trans_color = *trans_values;
        }
    }
}

void read_exif_chunk(png_structp png_ptr, png_infop info_ptr, file_meta_t* meta, error_info_t* err) {
    png_bytep exif;
    png_uint_32 exif_length;
    meta->png_info.chunks.has_exif = png_get_eXIf_1(png_ptr, info_ptr, &exif_length, &exif);
    if (meta->png_info.chunks.has_exif) {
        meta->png_info.chunks.exif = malloc(exif_length);
        if (meta->png_info.chunks.exif) {
            memcpy(meta->png_info.chunks.exif, exif, exif_length);
            meta->png_info.chunks.exif_length = exif_length;
        } else {
            set_err(err, ERR_MEM, ERROR_LOCATION_PNGPARSER);
        }
    }
}

void read_splt_chunks(png_structp png_ptr, png_infop info_ptr, file_meta_t* meta, error_info_t* err) {
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
                meta->png_info.chunks.splt_chunks[i].nentries = splt_ptr[i].nentries;
                size_t entry_size = splt_ptr[i].nentries * sizeof(png_sPLT_entry);
                meta->png_info.chunks.splt_chunks[i].entries = malloc(entry_size);
                if (meta->png_info.chunks.splt_chunks[i].entries) {
                    memcpy(meta->png_info.chunks.splt_chunks[i].entries, splt_ptr[i].entries, entry_size);
                } else {
                    set_err(err, ERR_MEM, ERROR_LOCATION_PNGPARSER);
                }
            }
        } else {
            set_err(err, ERR_MEM, ERROR_LOCATION_PNGPARSER);
        }
    }
}