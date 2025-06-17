#include "../include/outputinfo.h"

void print_PNG_info(file_meta_t* file_info) {
    printf("File format: PNG\n");
    printf("Image width: %d Image height: %d\n",\
    file_info->png_info.width, file_info->png_info.height);
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
    printf("Bit depth: %u\nChannels: %u\n",\
    file_info->png_info.bit_depth, file_info->png_info.channels);
}

void print_BMP_info(file_meta_t* file_info) {
    printf("File format: BMP");
    int bmp_format = file_info->bmp_info.info_header.header_size;
    switch (bmp_format) {
    case BITMAPCOREHEADER:
        printf(" v.CORE\n");
        break;
    case BITMAPINFOHEADER:
        printf(" v.3\n");
        break;
    case BITMAPV4HEADER:
        printf(" v.4\n");
        break;
    case BITMAPV5HEADER:
        printf(" v.5\n");
        break;
    default:
        break;
    }
    printf("Image resolution:\n");
    printf("\tWidth %d\n", file_info->bmp_info.info_header.width);
    printf("\tHeight %d\n", file_info->bmp_info.info_header.height);
    printf("Image size: %d byte\n", file_info->bmp_info.info_header.image_size);
    printf("Bits per pixel (bit depth): %d\n", file_info->bmp_info.info_header.bits_per_pixel);
    printf("Planes (1 as default value): %d\n", file_info->bmp_info.info_header.planes);
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
    printf("PPM: x %d; y %d (if 0, the values is not calculated)\n", file_info->bmp_info.info_header.x_PPM, file_info->bmp_info.info_header.y_PPM);
    printf("Colors in color table: %d\n", file_info->bmp_info.info_header.colors_in_color_table);
    printf("Important color count: %d\n", file_info->bmp_info.info_header.important_color_count);
    if (bmp_format > BITMAPCOREHEADER) {
        printf("Color bitmasks:\n");
        printf("\tRed 0x%X\n", file_info->bmp_info.info_header.red_channel_bitmask);
        printf("\tGreen 0x%X\n", file_info->bmp_info.info_header.green_channel_bitmask);
        printf("\tBlue 0x%X\n", file_info->bmp_info.info_header.blue_channel_bitmask);
        printf("\tAlpha 0x%X\n", file_info->bmp_info.info_header.alpha_channel_bitmask);
        if (bmp_format > BITMAPINFOHEADER) {
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
            BMP_endpoints_t endpoints = file_info->bmp_info.info_header.color_space_endpoints;
            printf("Color endpoints: \n");
            printf("\tRed: X 0x%x; Y 0x%x; Z 0x%x\n", endpoints.Red.ciexyzX, endpoints.Red.ciexyzY, endpoints.Red.ciexyzZ);
            printf("\tGreen: X 0x%x; Y 0x%x; Z 0x%x\n", endpoints.Green.ciexyzX, endpoints.Green.ciexyzY, endpoints.Green.ciexyzZ);
            printf("\tBlue: X 0x%x; Y 0x%x; Z 0x%x\n", endpoints.Blue.ciexyzX, endpoints.Blue.ciexyzY, endpoints.Blue.ciexyzZ);
            printf("Gamma for channels:\n");
            printf("\tRed: 0x%x\n", file_info->bmp_info.info_header.gamma_for_red_channel);
            printf("\tGreen: 0x%x\n", file_info->bmp_info.info_header.gamma_for_green_channel);
            printf("\tBlue: 0x%x\n", file_info->bmp_info.info_header.gamma_for_blue_channel);
            if (bmp_format > BITMAPV4HEADER) {
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
                printf("ICC_profile_data: %u\n", file_info->bmp_info.info_header.ICC_profile_data);
                printf("ICC_profile_size: %u\n", file_info->bmp_info.info_header.ICC_profile_size);
            }
        }
    }
}

void print_file_info(file_meta_t* file_info) {
    switch (file_info->format) {
    case PNG:
        print_PNG_info(file_info);
        break;
    case BMP:
        print_BMP_info(file_info);
        break;
    default:
        printf("File format: UNKNOWN\n");
        break;
    }
}