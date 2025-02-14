/*******************************************************************************
 * Size: 12 px
 * Bpp: 1
 * Opts: 
 ******************************************************************************/

#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "lvgl.h"
#endif

#ifndef FONT_SYMBOLS_12
#define FONT_SYMBOLS_12 1
#endif

#if FONT_SYMBOLS_12

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " */
    0x0,

    /* U+002D "-" */
    0xe0,

    /* U+002E "." */
    0x80,

    /* U+0030 "0" */
    0x79, 0x28, 0x61, 0x86, 0x18, 0x61, 0x49, 0xe0,

    /* U+0031 "1" */
    0x2e, 0x92, 0x49, 0x24,

    /* U+0032 "2" */
    0x74, 0x42, 0x11, 0x88, 0x88, 0xc7, 0xc0,

    /* U+0033 "3" */
    0x39, 0x10, 0x41, 0xc, 0xe0, 0x41, 0x5, 0xe0,

    /* U+0034 "4" */
    0x8, 0x61, 0x8a, 0x29, 0x28, 0xbf, 0x8, 0x20,

    /* U+0035 "5" */
    0xfc, 0x21, 0xf, 0x4c, 0x21, 0x9b, 0x80,

    /* U+0036 "6" */
    0x39, 0x18, 0x20, 0xbb, 0x38, 0x61, 0x4c, 0xe0,

    /* U+0037 "7" */
    0xfc, 0x10, 0x82, 0x10, 0x43, 0x8, 0x21, 0x0,

    /* U+0038 "8" */
    0x7a, 0x18, 0x61, 0x79, 0xe8, 0x61, 0x85, 0xe0,

    /* U+0039 "9" */
    0x73, 0x28, 0x61, 0x87, 0x37, 0x41, 0x89, 0xc0,

    /* U+0061 "a" */
    0x77, 0x38, 0x61, 0x87, 0x37, 0x40,

    /* U+0063 "c" */
    0x7e, 0x61, 0x8, 0x65, 0xe0,

    /* U+0064 "d" */
    0x4, 0x10, 0x5d, 0xce, 0x18, 0x61, 0xcd, 0xd0,

    /* U+0066 "f" */
    0x74, 0x4e, 0x44, 0x44, 0x44,

    /* U+0078 "x" */
    0x45, 0x23, 0x4, 0x39, 0x2c, 0x40,

    /* U+F100 "" */
    0x11, 0xb9, 0xf9, 0xd9, 0xce, 0x71, 0x9c, 0x46,

    /* U+F101 "" */
    0x8c, 0x77, 0x1d, 0xc6, 0x37, 0x77, 0x72, 0x30,

    /* U+F102 "" */
    0x18, 0x3c, 0x7e, 0xe7, 0x52, 0x1c, 0x7e, 0xe7,
    0xc3,

    /* U+F103 "" */
    0xc3, 0xe7, 0x7e, 0x1c, 0x52, 0xe7, 0x7e, 0x3c,
    0x18,

    /* U+F104 "" */
    0x17, 0xec, 0xe7, 0x10,

    /* U+F105 "" */
    0x8e, 0x73, 0x7e, 0x80,

    /* U+F106 "" */
    0x18, 0x3c, 0x7e, 0xe7, 0xc3,

    /* U+F107 "" */
    0xc3, 0xe7, 0x7e, 0x3c, 0x18,

    /* U+F498 "" */
    0xff, 0xf0, 0x6, 0xf4, 0xdf, 0x99, 0xe3, 0x0,
    0x60, 0xc, 0x3f, 0x87, 0xb0, 0x7, 0xff, 0x80,

    /* U+F499 "" */
    0xff, 0xf1, 0xc6, 0x44, 0xc8, 0x98, 0x33, 0x8,
    0x61, 0xc, 0x1, 0x84, 0x30, 0x7, 0xff, 0x80,

    /* U+F49A "" */
    0xff, 0xf0, 0x6, 0x28, 0xcd, 0x99, 0xf3, 0x1c,
    0x63, 0x8c, 0x71, 0x8e, 0x30, 0x7, 0xff, 0x80,

    /* U+F49B "" */
    0xff, 0xf0, 0x6, 0x0, 0xc8, 0x98, 0xa3, 0x8,
    0x62, 0x8c, 0x89, 0x80, 0x30, 0x7, 0xff, 0x80,

    /* U+F49C "" */
    0xff, 0xf0, 0x6, 0x0, 0xc0, 0x58, 0x13, 0x44,
    0x65, 0xc, 0x61, 0x80, 0x30, 0x7, 0xff, 0x80,

    /* U+F49D "" */
    0xff, 0xf0, 0x6, 0x0, 0xc0, 0x18, 0x3, 0x0,
    0x60, 0xc, 0x1, 0x80, 0x30, 0x7, 0xff, 0x80,

    /* U+F4C5 "" */
    0x2, 0x0, 0x70, 0xd, 0x1, 0x88, 0x30, 0xc7,
    0xf6, 0xdf, 0x3d, 0xeb, 0x30, 0x41, 0x98, 0xf,
    0x0, 0x20,

    /* U+F4C6 "" */
    0x4, 0x0, 0x60, 0xf, 0x0, 0x90, 0x19, 0x81,
    0x78, 0x31, 0xc2, 0x24, 0x42, 0x2f, 0xff,

    /* U+F4C7 "" */
    0xff, 0xf7, 0xfe, 0x40, 0x42, 0x44, 0x14, 0x81,
    0x48, 0xd, 0x0, 0x90, 0x6, 0x0, 0x40,

    /* U+F4C8 "" */
    0x1e, 0xc, 0x33, 0xcf, 0x5f, 0xa9, 0xe5, 0x3c,
    0xae, 0xd7, 0xbe, 0x61, 0x83, 0xc0,

    /* U+F4C9 "" */
    0xff, 0xe0, 0x18, 0x16, 0xd, 0x86, 0x6b, 0x1b,
    0x86, 0x41, 0x80, 0x7f, 0xf0,

    /* U+F4CA "" */
    0xff, 0xe0, 0x18, 0x6, 0x1, 0x80, 0x60, 0x18,
    0x6, 0x1, 0x80, 0x7f, 0xf0
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 75, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1, .adv_w = 82, .box_w = 3, .box_h = 1, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 2, .adv_w = 45, .box_w = 1, .box_h = 1, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 3, .adv_w = 115, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 11, .adv_w = 126, .box_w = 3, .box_h = 10, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 15, .adv_w = 116, .box_w = 5, .box_h = 10, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 22, .adv_w = 111, .box_w = 6, .box_h = 10, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 30, .adv_w = 118, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 38, .adv_w = 121, .box_w = 5, .box_h = 10, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 45, .adv_w = 117, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 53, .adv_w = 115, .box_w = 6, .box_h = 10, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 61, .adv_w = 115, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 69, .adv_w = 114, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 77, .adv_w = 110, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 83, .adv_w = 100, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 88, .adv_w = 110, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 96, .adv_w = 63, .box_w = 4, .box_h = 10, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 101, .adv_w = 103, .box_w = 6, .box_h = 7, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 107, .adv_w = 168, .box_w = 9, .box_h = 7, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 115, .adv_w = 168, .box_w = 9, .box_h = 7, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 123, .adv_w = 120, .box_w = 8, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 132, .adv_w = 120, .box_w = 8, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 141, .adv_w = 96, .box_w = 4, .box_h = 7, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 145, .adv_w = 96, .box_w = 4, .box_h = 7, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 149, .adv_w = 120, .box_w = 8, .box_h = 5, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 154, .adv_w = 120, .box_w = 8, .box_h = 5, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 159, .adv_w = 188, .box_w = 11, .box_h = 11, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 175, .adv_w = 195, .box_w = 11, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 191, .adv_w = 195, .box_w = 11, .box_h = 11, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 207, .adv_w = 188, .box_w = 11, .box_h = 11, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 223, .adv_w = 188, .box_w = 11, .box_h = 11, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 239, .adv_w = 188, .box_w = 11, .box_h = 11, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 255, .adv_w = 192, .box_w = 12, .box_h = 12, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 273, .adv_w = 192, .box_w = 12, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 288, .adv_w = 192, .box_w = 12, .box_h = 10, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 303, .adv_w = 192, .box_w = 11, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 317, .adv_w = 192, .box_w = 10, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 330, .adv_w = 192, .box_w = 10, .box_h = 10, .ofs_x = 1, .ofs_y = 0}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/

static const uint16_t unicode_list_0[] = {
    0x0, 0xd, 0xe, 0x10, 0x11, 0x12, 0x13, 0x14,
    0x15, 0x16, 0x17, 0x18, 0x19, 0x41, 0x43, 0x44,
    0x46, 0x58, 0xf0e0, 0xf0e1, 0xf0e2, 0xf0e3, 0xf0e4, 0xf0e5,
    0xf0e6, 0xf0e7, 0xf478, 0xf479, 0xf47a, 0xf47b, 0xf47c, 0xf47d,
    0xf4a5, 0xf4a6, 0xf4a7, 0xf4a8, 0xf4a9, 0xf4aa
};

/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] =
{
    {
        .range_start = 32, .range_length = 62635, .glyph_id_start = 1,
        .unicode_list = unicode_list_0, .glyph_id_ofs_list = NULL, .list_length = 38, .type = LV_FONT_FMT_TXT_CMAP_SPARSE_TINY
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
const lv_font_t font_Symbols_12 = {
#else
lv_font_t font_Symbols_12 = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 12,          /*The maximum line height required by the font*/
    .base_line = 1,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = -4,
    .underline_thickness = 1,
#endif
    .dsc = &font_dsc           /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
};



#endif /*#if FONT_SYMBOLS_12*/

