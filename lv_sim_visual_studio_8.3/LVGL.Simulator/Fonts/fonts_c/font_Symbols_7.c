/*******************************************************************************
 * Size: 7 px
 * Bpp: 1
 * Opts: 
 ******************************************************************************/

#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "lvgl.h"
#endif

#ifndef FONT_SYMBOLS_7
#define FONT_SYMBOLS_7 1
#endif

#if FONT_SYMBOLS_7

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
    0x80,

    /* U+0030 "0" */
    0x69, 0x99, 0x96,

    /* U+0031 "1" */
    0x55, 0x50,

    /* U+0032 "2" */
    0xc4, 0xa9, 0xc0,

    /* U+0033 "3" */
    0xc4, 0xa3, 0x80,

    /* U+0034 "4" */
    0x26, 0xaa, 0xf2,

    /* U+0035 "5" */
    0xf8, 0xe1, 0x1e,

    /* U+0036 "6" */
    0x78, 0xe9, 0x96,

    /* U+0037 "7" */
    0xe5, 0x29, 0x0,

    /* U+0038 "8" */
    0x69, 0x69, 0x96,

    /* U+0039 "9" */
    0x69, 0x97, 0x1e,

    /* U+0041 "A" */
    0x23, 0x14, 0xa7, 0x44,

    /* U+0043 "C" */
    0x78, 0x88, 0x87,

    /* U+0046 "F" */
    0xf2, 0x79, 0x0,

    /* U+0061 "a" */
    0x79, 0x97,

    /* U+0063 "c" */
    0x72, 0x30,

    /* U+0064 "d" */
    0x11, 0x79, 0x97,

    /* U+0066 "f" */
    0xee, 0xa0,

    /* U+0078 "x" */
    0xa6, 0x6a,

    /* U+F00C "" */
    0x6, 0x1b, 0x63, 0x82, 0x0,

    /* U+F021 "" */
    0x3a, 0x8e, 0x38, 0xe, 0x38, 0xae, 0x0,

    /* U+F051 "" */
    0x9d, 0xff, 0xd9,

    /* U+F053 "" */
    0x12, 0x4c, 0x21,

    /* U+F054 "" */
    0xc6, 0x33, 0x6c,

    /* U+F100 "" */
    0x2d, 0x65, 0x8b,

    /* U+F101 "" */
    0xd1, 0xa6, 0xb4,

    /* U+F102 "" */
    0x6f, 0x46, 0x90,

    /* U+F103 "" */
    0x96, 0x9f, 0x60,

    /* U+F104 "" */
    0x2b, 0x10,

    /* U+F105 "" */
    0xcd, 0xe0,

    /* U+F106 "" */
    0x6f, 0x90,

    /* U+F107 "" */
    0x96, 0x40,

    /* U+F498 "" */
    0xff, 0x76, 0xcc, 0x19, 0xf0, 0x7f, 0x80,

    /* U+F499 "" */
    0xff, 0x76, 0xac, 0x59, 0x32, 0x7f, 0x80,

    /* U+F49A "" */
    0xff, 0x6, 0xcc, 0x99, 0x30, 0x7f, 0x80,

    /* U+F49B "" */
    0xff, 0x6, 0xac, 0x9a, 0xb0, 0x7f, 0x80,

    /* U+F49C "" */
    0xff, 0x6, 0x2c, 0x9b, 0x30, 0x7f, 0x80,

    /* U+F49D "" */
    0xff, 0x6, 0xc, 0x18, 0x30, 0x7f, 0x80,

    /* U+F4C5 "" */
    0x8, 0x14, 0x62, 0x7b, 0x14, 0x8,

    /* U+F4C6 "" */
    0x10, 0x60, 0xa2, 0xc5, 0x5f, 0xc0,

    /* U+F4C7 "" */
    0xfe, 0xf9, 0x12, 0xc3, 0x86, 0x0,

    /* U+F4C8 "" */
    0x38, 0x8a, 0xed, 0x55, 0x47, 0x0,

    /* U+F4C9 "" */
    0xff, 0x6, 0x2f, 0x9a, 0x3f, 0xc0,

    /* U+F4CA "" */
    0xff, 0x6, 0xc, 0x18, 0x3f, 0xc0,

    /* U+F55A "" */
    0x3f, 0xba, 0xfe, 0xee, 0xb3, 0xf8
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 44, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1, .adv_w = 48, .box_w = 2, .box_h = 1, .ofs_x = 0, .ofs_y = 3},
    {.bitmap_index = 2, .adv_w = 26, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 3, .adv_w = 67, .box_w = 4, .box_h = 6, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 6, .adv_w = 73, .box_w = 2, .box_h = 6, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 8, .adv_w = 68, .box_w = 3, .box_h = 6, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 11, .adv_w = 65, .box_w = 3, .box_h = 6, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 14, .adv_w = 69, .box_w = 4, .box_h = 6, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 17, .adv_w = 70, .box_w = 4, .box_h = 6, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 20, .adv_w = 68, .box_w = 4, .box_h = 6, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 23, .adv_w = 67, .box_w = 3, .box_h = 6, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 26, .adv_w = 67, .box_w = 4, .box_h = 6, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 29, .adv_w = 67, .box_w = 4, .box_h = 6, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 32, .adv_w = 82, .box_w = 5, .box_h = 6, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 36, .adv_w = 78, .box_w = 4, .box_h = 6, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 39, .adv_w = 69, .box_w = 3, .box_h = 6, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 42, .adv_w = 64, .box_w = 4, .box_h = 4, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 44, .adv_w = 58, .box_w = 3, .box_h = 4, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 46, .adv_w = 64, .box_w = 4, .box_h = 6, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 49, .adv_w = 37, .box_w = 2, .box_h = 6, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 51, .adv_w = 60, .box_w = 4, .box_h = 4, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 53, .adv_w = 112, .box_w = 7, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 58, .adv_w = 112, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 65, .adv_w = 98, .box_w = 4, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 68, .adv_w = 70, .box_w = 4, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 71, .adv_w = 70, .box_w = 4, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 74, .adv_w = 98, .box_w = 6, .box_h = 4, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 77, .adv_w = 98, .box_w = 6, .box_h = 4, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 80, .adv_w = 70, .box_w = 4, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 83, .adv_w = 70, .box_w = 4, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 86, .adv_w = 56, .box_w = 3, .box_h = 4, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 88, .adv_w = 56, .box_w = 3, .box_h = 4, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 90, .adv_w = 70, .box_w = 4, .box_h = 3, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 92, .adv_w = 70, .box_w = 4, .box_h = 3, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 94, .adv_w = 109, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 101, .adv_w = 114, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 108, .adv_w = 114, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 115, .adv_w = 109, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 122, .adv_w = 109, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 129, .adv_w = 109, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 136, .adv_w = 112, .box_w = 8, .box_h = 6, .ofs_x = -1, .ofs_y = 0},
    {.bitmap_index = 142, .adv_w = 112, .box_w = 7, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 148, .adv_w = 112, .box_w = 7, .box_h = 6, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 154, .adv_w = 112, .box_w = 7, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 160, .adv_w = 112, .box_w = 7, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 166, .adv_w = 112, .box_w = 7, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 172, .adv_w = 140, .box_w = 9, .box_h = 5, .ofs_x = 0, .ofs_y = 0}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/

static const uint16_t unicode_list_0[] = {
    0x0, 0xd, 0xe, 0x10, 0x11, 0x12, 0x13, 0x14,
    0x15, 0x16, 0x17, 0x18, 0x19, 0x21, 0x23, 0x26,
    0x41, 0x43, 0x44, 0x46, 0x58, 0xefec, 0xf001, 0xf031,
    0xf033, 0xf034, 0xf0e0, 0xf0e1, 0xf0e2, 0xf0e3, 0xf0e4, 0xf0e5,
    0xf0e6, 0xf0e7, 0xf478, 0xf479, 0xf47a, 0xf47b, 0xf47c, 0xf47d,
    0xf4a5, 0xf4a6, 0xf4a7, 0xf4a8, 0xf4a9, 0xf4aa, 0xf53a
};

/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] =
{
    {
        .range_start = 32, .range_length = 62779, .glyph_id_start = 1,
        .unicode_list = unicode_list_0, .glyph_id_ofs_list = NULL, .list_length = 47, .type = LV_FONT_FMT_TXT_CMAP_SPARSE_TINY
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
const lv_font_t font_Symbols_7 = {
#else
lv_font_t font_Symbols_7 = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 8,          /*The maximum line height required by the font*/
    .base_line = 1,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = -2,
    .underline_thickness = 0,
#endif
    .dsc = &font_dsc           /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
};



#endif /*#if FONT_SYMBOLS_7*/

