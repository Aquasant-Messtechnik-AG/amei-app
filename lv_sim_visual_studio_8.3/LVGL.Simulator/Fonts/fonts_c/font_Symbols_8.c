/*******************************************************************************
 * Size: 8 px
 * Bpp: 1
 * Opts: 
 ******************************************************************************/

#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "lvgl.h"
#endif

#ifndef FONT_SYMBOLS_8
#define FONT_SYMBOLS_8 1
#endif

#if FONT_SYMBOLS_8

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " */
    0x0,

    /* U+002D "-" */
    0xc0,

    /* U+002E "." */
    0x0,

    /* U+0030 "0" */
    0x69, 0x99, 0x96,

    /* U+0031 "1" */
    0x75, 0x50,

    /* U+0032 "2" */
    0xf1, 0x12, 0x4f,

    /* U+0033 "3" */
    0xf1, 0x16, 0x1f,

    /* U+0034 "4" */
    0x11, 0x94, 0xaf, 0x88,

    /* U+0035 "5" */
    0xf8, 0xe1, 0x1e,

    /* U+0036 "6" */
    0x78, 0xe9, 0x96,

    /* U+0037 "7" */
    0xf1, 0x22, 0x44,

    /* U+0038 "8" */
    0xf9, 0xff, 0x9f,

    /* U+0039 "9" */
    0x69, 0x97, 0x1e,

    /* U+0041 "A" */
    0x20, 0xc5, 0x12, 0x7a, 0x10,

    /* U+0043 "C" */
    0x7c, 0x21, 0x8, 0x3c,

    /* U+0046 "F" */
    0xf8, 0x8f, 0x88,

    /* U+0061 "a" */
    0x79, 0x97,

    /* U+0063 "c" */
    0x78, 0x87,

    /* U+0064 "d" */
    0x11, 0x79, 0x97,

    /* U+0066 "f" */
    0x6b, 0xa4, 0x80,

    /* U+0078 "x" */
    0x96, 0x69,

    /* U+F00C "" */
    0x3, 0x7, 0xce, 0xfc, 0x78, 0x30,

    /* U+F021 "" */
    0x3d, 0x43, 0xc7, 0x0, 0x0, 0xe3, 0xc6, 0xbc,

    /* U+F051 "" */
    0x8e, 0x7f, 0xff, 0xe6, 0x20,

    /* U+F100 "" */
    0x36, 0xdb, 0x63, 0x63, 0x60,

    /* U+F101 "" */
    0xd8, 0xd8, 0xdb, 0x6d, 0x80,

    /* U+F102 "" */
    0x23, 0xb6, 0x47, 0x6c,

    /* U+F103 "" */
    0xdb, 0x89, 0xb7, 0x10,

    /* U+F104 "" */
    0x36, 0xc6, 0x30,

    /* U+F105 "" */
    0xc6, 0x36, 0xc0,

    /* U+F106 "" */
    0x23, 0xb7, 0x10,

    /* U+F107 "" */
    0x8e, 0xdc, 0x40,

    /* U+F498 "" */
    0xff, 0x81, 0xb5, 0xb9, 0x81, 0x8d, 0x99, 0xff,

    /* U+F499 "" */
    0xff, 0x9d, 0xa5, 0x85, 0x99, 0x81, 0x81, 0xff,

    /* U+F49A "" */
    0xff, 0x81, 0x99, 0x99, 0x89, 0x89, 0x81, 0xff,

    /* U+F49B "" */
    0xff, 0x81, 0xa5, 0x99, 0x99, 0xa5, 0x81, 0xff,

    /* U+F49C "" */
    0xff, 0x81, 0x81, 0x8d, 0xa9, 0x91, 0x81, 0xff,

    /* U+F49D "" */
    0xff, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0xff,

    /* U+F4C5 "" */
    0x8, 0x14, 0x22, 0x7a, 0xbd, 0x62, 0x1c,

    /* U+F4C6 "" */
    0x0, 0x18, 0x28, 0x3c, 0x4c, 0x4a, 0xff,

    /* U+F4C7 "" */
    0xff, 0x7e, 0x52, 0x54, 0x3c, 0x28, 0x10,

    /* U+F4C8 "" */
    0x3c, 0x42, 0xbe, 0x9a, 0xbe, 0x42, 0x3c,

    /* U+F4C9 "" */
    0xff, 0xe, 0x3c, 0xdb, 0x30, 0x7f, 0x80,

    /* U+F4CA "" */
    0xff, 0x6, 0xc, 0x18, 0x30, 0x7f, 0x80,

    /* U+F55A "" */
    0x3f, 0xdf, 0xff, 0x9f, 0xe7, 0x7f, 0xcf, 0xf0
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 50, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1, .adv_w = 55, .box_w = 2, .box_h = 1, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 2, .adv_w = 30, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 3, .adv_w = 77, .box_w = 4, .box_h = 6, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 6, .adv_w = 84, .box_w = 2, .box_h = 6, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 8, .adv_w = 78, .box_w = 4, .box_h = 6, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 11, .adv_w = 74, .box_w = 4, .box_h = 6, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 14, .adv_w = 79, .box_w = 5, .box_h = 6, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 18, .adv_w = 81, .box_w = 4, .box_h = 6, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 21, .adv_w = 78, .box_w = 4, .box_h = 6, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 24, .adv_w = 77, .box_w = 4, .box_h = 6, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 27, .adv_w = 77, .box_w = 4, .box_h = 6, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 30, .adv_w = 76, .box_w = 4, .box_h = 6, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 33, .adv_w = 94, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 38, .adv_w = 89, .box_w = 5, .box_h = 6, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 42, .adv_w = 79, .box_w = 4, .box_h = 6, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 45, .adv_w = 73, .box_w = 4, .box_h = 4, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 47, .adv_w = 67, .box_w = 4, .box_h = 4, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 49, .adv_w = 73, .box_w = 4, .box_h = 6, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 52, .adv_w = 42, .box_w = 3, .box_h = 6, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 55, .adv_w = 69, .box_w = 4, .box_h = 4, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 57, .adv_w = 128, .box_w = 8, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 63, .adv_w = 128, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 71, .adv_w = 112, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 76, .adv_w = 112, .box_w = 7, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 81, .adv_w = 112, .box_w = 7, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 86, .adv_w = 80, .box_w = 5, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 90, .adv_w = 80, .box_w = 5, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 94, .adv_w = 64, .box_w = 4, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 97, .adv_w = 64, .box_w = 4, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 100, .adv_w = 80, .box_w = 5, .box_h = 4, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 103, .adv_w = 80, .box_w = 5, .box_h = 4, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 106, .adv_w = 125, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 114, .adv_w = 130, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 122, .adv_w = 130, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 130, .adv_w = 125, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 138, .adv_w = 125, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 146, .adv_w = 125, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 154, .adv_w = 128, .box_w = 8, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 161, .adv_w = 128, .box_w = 8, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 168, .adv_w = 128, .box_w = 8, .box_h = 7, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 175, .adv_w = 128, .box_w = 8, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 182, .adv_w = 128, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 189, .adv_w = 128, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 196, .adv_w = 160, .box_w = 10, .box_h = 6, .ofs_x = 0, .ofs_y = 0}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/

static const uint16_t unicode_list_0[] = {
    0x0, 0xd, 0xe, 0x10, 0x11, 0x12, 0x13, 0x14,
    0x15, 0x16, 0x17, 0x18, 0x19, 0x21, 0x23, 0x26,
    0x41, 0x43, 0x44, 0x46, 0x58, 0xefec, 0xf001, 0xf031,
    0xf0e0, 0xf0e1, 0xf0e2, 0xf0e3, 0xf0e4, 0xf0e5, 0xf0e6, 0xf0e7,
    0xf478, 0xf479, 0xf47a, 0xf47b, 0xf47c, 0xf47d, 0xf4a5, 0xf4a6,
    0xf4a7, 0xf4a8, 0xf4a9, 0xf4aa, 0xf53a
};

/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] =
{
    {
        .range_start = 32, .range_length = 62779, .glyph_id_start = 1,
        .unicode_list = unicode_list_0, .glyph_id_ofs_list = NULL, .list_length = 45, .type = LV_FONT_FMT_TXT_CMAP_SPARSE_TINY
    }
};



/*--------------------
 *  ALL CUSTOM DATA
 *--------------------*/

#if LV_VERSION_CHECK(8, 0, 0)
/*Store all the custom data of the font*/
static  lv_font_fmt_txt_glyph_cache_t cache;
static const lv_font_fmt_txt_dsc_t font_dsc = {
#else
static lv_font_fmt_txt_dsc_t font_dsc = {
#endif
    .glyph_bitmap = glyph_bitmap,
    .glyph_dsc = glyph_dsc,
    .cmaps = cmaps,
    .kern_dsc = NULL,
    .kern_scale = 0,
    .cmap_num = 1,
    .bpp = 1,
    .kern_classes = 0,
    .bitmap_format = 0,
#if LV_VERSION_CHECK(8, 0, 0)
    .cache = &cache
#endif
};


/*-----------------
 *  PUBLIC FONT
 *----------------*/

/*Initialize a public general font descriptor*/
#if LV_VERSION_CHECK(8, 0, 0)
const lv_font_t font_Symbols_8 = {
#else
lv_font_t font_Symbols_8 = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 9,          /*The maximum line height required by the font*/
    .base_line = 1,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = -3,
    .underline_thickness = 0,
#endif
    .dsc = &font_dsc           /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
};



#endif /*#if FONT_SYMBOLS_8*/

