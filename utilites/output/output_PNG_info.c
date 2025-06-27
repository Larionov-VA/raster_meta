#include "../../include/output_PNG_info.h"

void print_all_PNG_info(file_meta_t* file_info) {
    print_PNG_file_format();
    print_PNG_resolution(file_info);
    print_PNG_colortype(file_info);
    print_PNG_bitdepth(file_info);
    print_PNG_tEXt_chunk(file_info);
    print_PNG_tIME_chunk(file_info);
    print_PNG_gAMA_chunk(file_info);
    print_PNG_cHRM_chunk(file_info);
    print_PNG_sRGB_chunk(file_info);
    print_PNG_iCCP_chunk(file_info);
    print_PNG_sBIT_chunk(file_info);
    print_PNG_hIST_chunk(file_info);
    print_PNG_pHYs_chunk(file_info);
    print_PNG_bKGD_chunk(file_info);
    print_PNG_tRNS_chunk(file_info);
    print_PNG_eXIf_chunk(file_info);
    print_PNG_sPLT_chunk(file_info);
}

void print_PNG_file_format() {
    printf("File format: PNG\n");
}

void print_PNG_resolution(file_meta_t* file_info) {
    printf("Image width: %d Image height: %d\n", file_info->png_info.width, file_info->png_info.height);
}

void print_PNG_colortype(file_meta_t* file_info) {
    switch (file_info->png_info.color_type) {
    case PNG_COLOR_TYPE_GRAY:
        printf("Color type: GRAY\n");
        break;
    case PNG_COLOR_TYPE_PALETTE:
        printf("Color type: PALETTE\n");
        break;
    case PNG_COLOR_TYPE_RGB:
        printf("Color type: RGB\n");
        break;
    case PNG_COLOR_TYPE_RGBA:
        printf("Color type: RGBA\n");
        break;
    case PNG_COLOR_TYPE_GA:
        printf("Color type: GA\n");
        break;
    default:
        printf("Color type: %d\n", file_info->png_info.color_type);
    }
}

void print_PNG_bitdepth(file_meta_t* file_info) {
    printf("Bit depth: %u\n", file_info->png_info.bit_depth);
}

void print_PNG_tEXt_chunk(file_meta_t* file_info) {
    printf("Found %d text chunk(s):\n", file_info->png_info.chunks.num_text_chunks);
    for (int i = 0; i < file_info->png_info.chunks.num_text_chunks; i++) {
        printf("\t%s: %s\n", file_info->png_info.chunks.text_chunks[i].key, file_info->png_info.chunks.text_chunks[i].text);
    }
}

void print_PNG_tIME_chunk(file_meta_t* file_info) {
    if (file_info->png_info.chunks.has_time_chunk) {
        printf("Modification time: ");
        printf("%d-%02d-%02d %02d:%02d:%02d\n",
            file_info->png_info.chunks.time_chunk.year,
            file_info->png_info.chunks.time_chunk.month,
            file_info->png_info.chunks.time_chunk.day,
            file_info->png_info.chunks.time_chunk.hour,
            file_info->png_info.chunks.time_chunk.minute,
            file_info->png_info.chunks.time_chunk.second);
    }
}

void print_PNG_gAMA_chunk(file_meta_t* file_info) {
    if (file_info->png_info.chunks.has_gama) {
        printf("gAMA (gamma): %.6f\n", file_info->png_info.chunks.gamma);
    }
}

void print_PNG_cHRM_chunk(file_meta_t* file_info) {
    if (file_info->png_info.chunks.has_chrm) {
        printf("cHRM (chromaticity):\n");
        printf("\tWhite point: x=%.6f, y=%.6f\n", file_info->png_info.chunks.white_x, file_info->png_info.chunks.white_y);
        printf("\tRed:   x=%.6f, y=%.6f\n", file_info->png_info.chunks.red_x, file_info->png_info.chunks.red_y);
        printf("\tGreen: x=%.6f, y=%.6f\n", file_info->png_info.chunks.green_x, file_info->png_info.chunks.green_y);
        printf("\tBlue:  x=%.6f, y=%.6f\n", file_info->png_info.chunks.blue_x, file_info->png_info.chunks.blue_y);
    }
}

void print_PNG_sRGB_chunk(file_meta_t* file_info) {
    if (file_info->png_info.chunks.has_srgb) {
        const char* intent_str = "Unknown";
        switch (file_info->png_info.chunks.srgb_intent) {
        case PNG_sRGB_INTENT_PERCEPTUAL:
            intent_str = "Perceptual";
            break;
        case PNG_sRGB_INTENT_RELATIVE:
            intent_str = "Relative";
            break;
        case PNG_sRGB_INTENT_SATURATION:
            intent_str = "Saturation";
            break;
        case PNG_sRGB_INTENT_ABSOLUTE:
            intent_str = "Absolute";
            break;
        }
        printf("sRGB rendering intent: %s\n", intent_str);
    }
}

void print_PNG_iCCP_chunk(file_meta_t* file_info) {
    if (file_info->png_info.chunks.has_iccp) {
        printf("iCCP profile: %s\n", file_info->png_info.chunks.iccp_name);
        printf("\tCompression: %s\n", file_info->png_info.chunks.iccp_compression ? "Deflate" : "None");
        printf("\tProfile size: %u bytes\n", file_info->png_info.chunks.iccp_proflen);
    }
}

void print_PNG_sBIT_chunk(file_meta_t* file_info) {
    if (file_info->png_info.chunks.has_sbit) {
        png_color_8 sbit = file_info->png_info.chunks.sbit;
        printf("sBIT (significant bits):\n");
        if (sbit.red) {
            printf("\tRed: %u\n", sbit.red);
        }
        if (sbit.green) {
            printf("\tGreen: %u\n", sbit.green);
        }
        if (sbit.blue) {
            printf("\tBlue: %u\n", sbit.blue);
        }
        if (sbit.alpha) {
            printf("\tAlpha: %u\n", sbit.alpha);
        }
        if (sbit.gray) {
            printf("\tGray: %u\n", sbit.gray);
        }
    }
}

void print_PNG_hIST_chunk(file_meta_t* file_info) {
    if (file_info->png_info.chunks.has_hist) {
        printf("hIST (color histogram):\n");
        for (int i = 0; i < file_info->png_info.chunks.num_hist_entries; i++) {
            printf("\tPalette index %d: frequency %u\n", i, file_info->png_info.chunks.hist[i]);
        }
    }
}

void print_PNG_pHYs_chunk(file_meta_t* file_info) {
    if (file_info->png_info.chunks.has_phys) {
        printf("pHYs (physical dimensions):\n");
        printf("\tPixels per unit: X=%u, Y=%u\n", file_info->png_info.chunks.phys_x, file_info->png_info.chunks.phys_y);
        char* unit_str = "Unknown";
        if (file_info->png_info.chunks.phys_unit_type == PNG_RESOLUTION_METER) {
            unit_str = "Meters";
        }
        printf("\tUnit: %s\n", unit_str);
    }
}

void print_PNG_bKGD_chunk(file_meta_t* file_info) {
    if (file_info->png_info.chunks.has_bkgd) {
        png_color_16 bkgd = file_info->png_info.chunks.bkgd;
        printf("bKGD (background color):\n");
        if (file_info->png_info.color_type & PNG_COLOR_MASK_COLOR) {
            printf("\tRGB: %u, %u, %u\n", bkgd.red, bkgd.green, bkgd.blue);
        } else {
            printf("\tGray: %u\n", bkgd.gray);
        }
    }
}

void print_PNG_tRNS_chunk(file_meta_t* file_info) {
    if (file_info->png_info.chunks.has_trns) {
        printf("tRNS (transparency):\n");
        if (file_info->png_info.color_type == PNG_COLOR_TYPE_PALETTE) {
            printf("\tAlpha entries: %d\n", file_info->png_info.chunks.num_trans);
        } else if (file_info->png_info.color_type == PNG_COLOR_TYPE_RGB) {
            printf("\tTransparent color: RGB(%u, %u, %u)\n",
                   file_info->png_info.chunks.trans_color.red,
                   file_info->png_info.chunks.trans_color.green,
                   file_info->png_info.chunks.trans_color.blue);
        } else if (file_info->png_info.color_type == PNG_COLOR_TYPE_GRAY) {
            printf("\tTransparent gray: %u\n", file_info->png_info.chunks.trans_color.gray);
        }
    }
}

void print_PNG_eXIf_chunk(file_meta_t* file_info) {
    if (file_info->png_info.chunks.has_exif) {
        printf("eXIf chunk present\n");
        printf("\tExif data size: %u bytes\n", file_info->png_info.chunks.exif_length);
    }
}

void print_PNG_sPLT_chunk(file_meta_t* file_info) {
    if (file_info->png_info.chunks.num_splt_chunks > 0) {
        printf("Found %d sPLT chunk(s):\n", file_info->png_info.chunks.num_splt_chunks);
        for (int i = 0; i < file_info->png_info.chunks.num_splt_chunks; i++) {
            png_sPLT_t splt = file_info->png_info.chunks.splt_chunks[i];
            printf("\tPalette: %s\n", splt.name);
            printf("\tDepth: %d\n", splt.depth);
            printf("\tEntries: %d\n", splt.nentries);
        }
    }
}