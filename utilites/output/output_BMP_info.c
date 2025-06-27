#include "../../include/output_BMP_info.h"

void print_all_BMP_info(file_meta_t* file_info) {
    int bmp_format = file_info->bmp_info.info_header.header_size;
    print_BMP_file_format(bmp_format);
    print_BMP_resolution(file_info);
    print_BMP_size(file_info);
    print_BMP_bitdepth(file_info);
    print_BMP_planes(file_info);
    print_BMP_compression(file_info);
    print_BMP_PPM(file_info);
    print_BMP_color_in_color_table(file_info);
    print_BMP_important_color_count(file_info);
    if (bmp_format > BITMAPCOREHEADER) {
        print_BMP_color_bitmasks(file_info);
        if (bmp_format > BITMAPV3INFOHEADER) {
            print_BMP_color_space_type(file_info);
            print_BMP_color_endpoints(file_info);
            print_BMP_gamma_for_channels(file_info);
            if (bmp_format > BITMAPV4HEADER) {
                print_BMP_intent(file_info);
                print_BMP_ICC_profile_data(file_info);
                print_BMP_ICC_profile_size(file_info);
            }
        }
    }
}

void print_BMP_file_format(int bmp_format) {
    printf("File format: BMP");
    switch (bmp_format) {
    case BITMAPCOREHEADER:
        printf(" v.CORE\n");
        break;
    case BITMAPINFOHEADER:
        printf(" v.3\n");
        break;
    case BITMAPV2INFOHEADER:
        printf(" v.2\n");
        break;
    case BITMAPV3INFOHEADER:
        printf(" v.3\n");
        break;
    case BITMAPV4HEADER:
        printf(" v.4\n");
        break;
    case BITMAPV5HEADER:
        printf(" v.5\n");
        break;
    default:
        printf(" v.? header_size = %d byte(-s)\n", bmp_format);
        break;
    }
}

void print_BMP_resolution(file_meta_t* file_info) {
    printf("Image resolution:\n");
    printf("\tWidth %d\n", file_info->bmp_info.info_header.width);
    printf("\tHeight %d\n", file_info->bmp_info.info_header.height);
}

void print_BMP_size(file_meta_t* file_info) {
    printf("Image size: %d bytes\n", file_info->bmp_info.info_header.image_size);
}

void print_BMP_bitdepth(file_meta_t* file_info) {
    printf("Bits per pixel (bit depth): %d\n", file_info->bmp_info.info_header.bits_per_pixel);
}

void print_BMP_planes(file_meta_t* file_info) {
    printf("Planes (1 as default value): %d\n", file_info->bmp_info.info_header.planes);
}

void print_BMP_compression(file_meta_t* file_info) {
    switch (file_info->bmp_info.info_header.compression)
    {
    case BI_RGB:
        printf("Compression type: BI_RGB (2D array)\n");
        break;
    case BI_RLE8:
        printf("Compression type: BI_RLE8 (RLE encoding)\n");
        break;
    case BI_RLE4:
        printf("Compression type: BI_RLE4 (RLE encoding)\n");
        break;
    case BI_BITFIELDS:
        printf("Compression type: BI_BITFIELDS (2D array with color channel masks)\n");
        break;
    case BI_JPEG:
        printf("Compression type: BI_JPEG (in the embedded JPEG file)\n");
        break;
    case BI_PNG:
        printf("Compression type: BI_PNG (in the embedded PNG file)\n");
        break;
    case BI_ALPHABITFIELDS:
        printf("Compression type: BI_ALPHABITFIELDS (2D array with color and alpha channel masks)\n");
        break;
    default:
        printf("Compression type: unknown type (or read error)\n");
        break;
    }
}

void print_BMP_PPM(file_meta_t* file_info) {
    printf("PPM: x %d; y %d (if 0, the values is not calculated)\n", file_info->bmp_info.info_header.x_PPM, file_info->bmp_info.info_header.y_PPM);
}

void print_BMP_color_in_color_table(file_meta_t* file_info) {
    printf("Colors in color table: %d\n", file_info->bmp_info.info_header.colors_in_color_table);
}

void print_BMP_important_color_count(file_meta_t* file_info) {
    printf("Important color count: %d\n", file_info->bmp_info.info_header.important_color_count);
}

void print_BMP_color_bitmasks(file_meta_t* file_info) {
    printf("Color bitmasks:\n");
    printf("\tRed 0x%X\n", file_info->bmp_info.info_header.red_channel_bitmask);
    printf("\tGreen 0x%X\n", file_info->bmp_info.info_header.green_channel_bitmask);
    printf("\tBlue 0x%X\n", file_info->bmp_info.info_header.blue_channel_bitmask);
    printf("\tAlpha 0x%X\n", file_info->bmp_info.info_header.alpha_channel_bitmask);
}

void print_BMP_color_space_type(file_meta_t* file_info) {
    switch (file_info->bmp_info.info_header.color_space_type) {
    case SRGB:
        printf("Color space type: sRGB\n");
        break;
    case WIN:
        printf("Color space type: default on device\n");
        break;
    case LINK:
        printf("Color space type: color profile in another file.\n");
        break;
    case MBED:
        printf("Color space type: the color profile included in this file.\n");
        break;
    default:
        printf("Color space type: adjustment based on endpoints and gamma values.\n");
        break;
    }
}

void print_BMP_color_endpoints(file_meta_t* file_info) {
    BMP_endpoints_t endpoints = file_info->bmp_info.info_header.color_space_endpoints;
    printf("Color endpoints: \n");
    printf("\tRed: X 0x%x; Y 0x%x; Z 0x%x\n", endpoints.Red.ciexyzX, endpoints.Red.ciexyzY, endpoints.Red.ciexyzZ);
    printf("\tGreen: X 0x%x; Y 0x%x; Z 0x%x\n", endpoints.Green.ciexyzX, endpoints.Green.ciexyzY, endpoints.Green.ciexyzZ);
    printf("\tBlue: X 0x%x; Y 0x%x; Z 0x%x\n", endpoints.Blue.ciexyzX, endpoints.Blue.ciexyzY, endpoints.Blue.ciexyzZ);
}

void print_BMP_gamma_for_channels(file_meta_t* file_info) {
    printf("Gamma for channels:\n");
    printf("\tRed: 0x%x\n", file_info->bmp_info.info_header.gamma_for_red_channel);
    printf("\tGreen: 0x%x\n", file_info->bmp_info.info_header.gamma_for_green_channel);
    printf("\tBlue: 0x%x\n", file_info->bmp_info.info_header.gamma_for_blue_channel);
}

void print_BMP_intent(file_meta_t* file_info) {
    switch (file_info->bmp_info.info_header.intent) {
    case LCS_GM_BUSINESS:
        printf("intent: saturation (Graphic)\n");
        break;
    case LCS_GM_GRAPHICS:
        printf("intent: media-relative colorimetric (Proof)\n");
        break;
    case LCS_GM_IMAGES:
        printf("intent: perceptual (Picture)\n");
        break;
    case LCS_GM_ABS_COLORIMETRIC:
        printf("intent: relative colometric (Match)\n");
        break;
    default:
        printf("intent: unknown (error)\n");
        break;
    }
}

void print_BMP_ICC_profile_data(file_meta_t* file_info) {
    printf("ICC_profile_data: %u\n", file_info->bmp_info.info_header.ICC_profile_data);
}

void print_BMP_ICC_profile_size(file_meta_t* file_info) {
    printf("ICC_profile_size: %u\n", file_info->bmp_info.info_header.ICC_profile_size);
}