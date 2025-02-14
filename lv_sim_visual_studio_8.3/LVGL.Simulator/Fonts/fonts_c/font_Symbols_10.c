/*******************************************************************************
 * Size: 10 px
 * Bpp: 1
 * Opts: 
 ******************************************************************************/

#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "lvgl.h"
#endif

#ifndef FONT_SYMBOLS_10
#define FONT_SYMBOLS_10 1
#endif

#if FONT_SYMBOLS_10

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
    0x76, 0xe3, 0x18, 0xed, 0xc0,

    /* U+0031 "1" */
    0x75, 0x54,

    /* U+0032 "2" */
    0x70, 0x42, 0x22, 0x23, 0xe0,

    /* U+0033 "3" */
    0x70, 0x42, 0x60, 0xc5, 0xc0,

    /* U+0034 "4" */
    0x8, 0x62, 0x8a, 0x4b, 0xf0, 0x80,

    /* U+0035 "5" */
    0xfc, 0x3d, 0x10, 0xc5, 0xc0,

    /* U+0036 "6" */
    0x76, 0x2d, 0x98, 0xe5, 0xc0,

    /* U+0037 "7" */
    0xf8, 0x44, 0x22, 0x21, 0x0,

    /* U+0038 "8" */
    0x74, 0x62, 0xe8, 0xc5, 0xc0,

    /* U+0039 "9" */
    0x74, 0x63, 0x17, 0x87, 0xc0,

    /* U+0061 "a" */
    0x6c, 0xe3, 0x17, 0x80,

    /* U+0063 "c" */
    0x78, 0x88, 0x70,

    /* U+0064 "d" */
    0x8, 0x5f, 0x18, 0xc5, 0xe0,

    /* U+0066 "f" */
    0x6b, 0xa4, 0x90,

    /* U+0078 "x" */
    0x4a, 0x88, 0xa4, 0x80,

    /* U+F100 "" */
    0x11, 0x33, 0x66, 0x6e, 0x33, 0x11,

    /* U+F101 "" */
    0x4c, 0x66, 0x33, 0x33, 0x66, 0x4c,

    /* U+F102 "" */
    0x0, 0xc7, 0xb3, 0x31, 0xe7, 0xb3,

    /* U+F103 "" */
    0x3, 0x37, 0x8c, 0x87, 0x37, 0x8c,

    /* U+F104 "" */
    0x11, 0x98, 0xc3, 0x8,

    /* U+F105 "" */
    0x43, 0xc, 0x66, 0x20,

    /* U+F106 "" */
    0x20, 0xc7, 0xb3,

    /* U+F107 "" */
    0x87, 0x37, 0x8c,

    /* U+F498 "" */
    0xff, 0xe0, 0x18, 0x6, 0x1, 0xb0, 0x63, 0x98,
    0x6, 0x1, 0x80, 0x7f, 0xf0,

    /* U+F499 "" */
    0xff, 0xf0, 0xa, 0x39, 0x27, 0x44, 0xf0, 0x4a,
    0x5, 0x80, 0x90, 0xc, 0x0, 0x80,

    /* U+F49A "" */
    0xff, 0xe0, 0x14, 0xc9, 0x34, 0x25, 0x9, 0x81,
    0x20, 0x30, 0x4, 0x0,

    /* U+F49B "" */
    0xff, 0xe0, 0x18, 0x6, 0x49, 0x8c, 0x63, 0x19,
    0x26, 0x1, 0x80, 0x7f, 0xf0,

    /* U+F49C "" */
    0xff, 0xe0, 0x18, 0x6, 0x1, 0x82, 0x69, 0x19,
    0x86, 0x1, 0x80, 0x7f, 0xf0,

    /* U+F49D "" */
    0xff, 0xe0, 0x18, 0x6, 0x1, 0x80, 0x60, 0x18,
    0x6, 0x1, 0x80, 0x7f, 0xf0,

    /* U+F4C5 "" */
    0x4, 0x2, 0x81, 0x20, 0x84, 0x5c, 0xa7, 0xb6,
    0x18, 0x68, 0xc, 0x0,

    /* U+F4C6 "" */
    0xc, 0x3, 0x1, 0x20, 0x58, 0x23, 0x9, 0x44,
    0x4b, 0xff,

    /* U+F4C7 "" */
    0xff, 0xdf, 0xe4, 0x88, 0xa4, 0x2a, 0x6, 0x81,
    0x40, 0x30, 0x0, 0x0,

    /* U+F4C8 "" */
    0x3c, 0x21, 0x29, 0x5f, 0xa9, 0x95, 0xeb, 0x9c,
    0x84, 0x3c, 0x0,

    /* U+F4C9 "" */
    0xff, 0xc0, 0x60, 0xb0, 0xda, 0xcd, 0xc6, 0x43,
    0x1, 0xff, 0x80,

    /* U+F4CA "" */
    0xff, 0xc0, 0x60, 0x30, 0x18, 0xc, 0x6, 0x3,
    0x1, 0xff, 0x80
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 63, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1, .adv_w = 68, .box_w = 3, .box_h = 1, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 2, .adv_w = 37, .box_w = 1, .box_h = 1, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 3, .adv_w = 96, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 8, .adv_w = 105, .box_w = 2, .box_h = 7, .ofs_x = 2, .ofs_y = 1},
    {.bitmap_index = 10, .adv_w = 97, .box_w = 5, .box_h = 7, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 15, .adv_w = 93, .box_w = 5, .box_h = 7, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 20, .adv_w = 98, .box_w = 6, .box_h = 7, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 26, .adv_w = 101, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 31, .adv_w = 97, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 36, .adv_w = 96, .box_w = 5, .box_h = 7, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 41, .adv_w = 96, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 46, .adv_w = 95, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 51, .adv_w = 91, .box_w = 5, .box_h = 5, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 55, .adv_w = 83, .box_w = 4, .box_h = 5, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 58, .adv_w = 91, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 63, .adv_w = 53, .box_w = 3, .box_h = 7, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 66, .adv_w = 86, .box_w = 5, .box_h = 5, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 70, .adv_w = 140, .box_w = 8, .box_h = 6, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 76, .adv_w = 140, .box_w = 8, .box_h = 6, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 82, .adv_w = 100, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 88, .adv_w = 100, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 94, .adv_w = 80, .box_w = 5, .box_h = 6, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 98, .adv_w = 80, .box_w = 5, .box_h = 6, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 102, .adv_w = 100, .box_w = 6, .box_h = 4, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 105, .adv_w = 100, .box_w = 6, .box_h = 4, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 108, .adv_w = 156, .box_w = 10, .box_h = 10, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 121, .adv_w = 163, .box_w = 11, .box_h = 10, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 135, .adv_w = 162, .box_w = 10, .box_h = 9, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 147, .adv_w = 156, .box_w = 10, .box_h = 10, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 160, .adv_w = 156, .box_w = 10, .box_h = 10, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 173, .adv_w = 156, .box_w = 10, .box_h = 10, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 186, .adv_w = 160, .box_w = 10, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 198, .adv_w = 160, .box_w = 10, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 208, .adv_w = 160, .box_w = 10, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 220, .adv_w = 160, .box_w = 9, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 231, .adv_w = 160, .box_w = 9, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 242, .adv_w = 160, .box_w = 9, .box_h = 9, .ofs_x = 1, .ofs_y = 0}
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
const lv_font_t font_Symbols_10 = {
#else
lv_font_t font_Symbols_10 = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 10,          /*The maximum line height required by the font*/
    .base_line = 1,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = -4,
    .underline_thickness = 0,
#endif
    .dsc = &font_dsc           /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
};



#endif /*#if FONT_SYMBOLS_10*/

