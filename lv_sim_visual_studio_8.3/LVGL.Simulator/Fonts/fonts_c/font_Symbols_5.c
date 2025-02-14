/*******************************************************************************
 * Size: 5 px
 * Bpp: 1
 * Opts: 
 ******************************************************************************/

#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "lvgl.h"
#endif

#ifndef FONT_SYMBOLS_5
#define FONT_SYMBOLS_5 1
#endif

#if FONT_SYMBOLS_5

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
    0xd7, 0x0,

    /* U+0031 "1" */
    0xe0,

    /* U+0032 "2" */
    0x6b, 0x0,

    /* U+0033 "3" */
    0x6b, 0x80,

    /* U+0034 "4" */
    0x7c,

    /* U+0035 "5" */
    0xc7, 0x0,

    /* U+0036 "6" */
    0x57, 0x0,

    /* U+0037 "7" */
    0x68,

    /* U+0038 "8" */
    0xeb, 0x80,

    /* U+0039 "9" */
    0xcf, 0x0,

    /* U+0061 "a" */
    0xfc,

    /* U+0063 "c" */
    0xa0,

    /* U+0064 "d" */
    0x3f, 0x80,

    /* U+0066 "f" */
    0xe0,

    /* U+0078 "x" */
    0x18,

    /* U+F100 "" */
    0x5a, 0x50,

    /* U+F101 "" */
    0xa5, 0xa0,

    /* U+F102 "" */
    0x55, 0x50,

    /* U+F103 "" */
    0xaa, 0xa0,

    /* U+F104 "" */
    0x64,

    /* U+F105 "" */
    0x98,

    /* U+F106 "" */
    0x54,

    /* U+F107 "" */
    0xa8,

    /* U+F498 "" */
    0xfc, 0x63, 0x78, 0xfc,

    /* U+F499 "" */
    0xfd, 0xac, 0xa2, 0x0,

    /* U+F49A "" */
    0xf9, 0xa5, 0x8,

    /* U+F49B "" */
    0xfc, 0x63, 0x18, 0xfc,

    /* U+F49C "" */
    0xfc, 0x63, 0x58, 0xfc,

    /* U+F49D "" */
    0xfc, 0x63, 0x18, 0xfc,

    /* U+F4C5 "" */
    0x11, 0xb7, 0x46,

    /* U+F4C6 "" */
    0x63, 0x2d, 0xf0,

    /* U+F4C7 "" */
    0xfb, 0xa4, 0xc6, 0x0,

    /* U+F4C8 "" */
    0x76, 0xea, 0xa7, 0x0,

    /* U+F4C9 "" */
    0xfc, 0xfb, 0x1f, 0x80,

    /* U+F4CA "" */
    0xfc, 0x63, 0x1f, 0x80
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 31, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1, .adv_w = 34, .box_w = 2, .box_h = 1, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 2, .adv_w = 19, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 3, .adv_w = 48, .box_w = 3, .box_h = 3, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 5, .adv_w = 52, .box_w = 1, .box_h = 3, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 6, .adv_w = 48, .box_w = 3, .box_h = 3, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 8, .adv_w = 46, .box_w = 3, .box_h = 3, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 10, .adv_w = 49, .box_w = 2, .box_h = 3, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 11, .adv_w = 50, .box_w = 3, .box_h = 3, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 13, .adv_w = 49, .box_w = 3, .box_h = 3, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 15, .adv_w = 48, .box_w = 2, .box_h = 3, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 16, .adv_w = 48, .box_w = 3, .box_h = 3, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 18, .adv_w = 48, .box_w = 3, .box_h = 3, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 20, .adv_w = 46, .box_w = 3, .box_h = 2, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 21, .adv_w = 42, .box_w = 2, .box_h = 2, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 22, .adv_w = 46, .box_w = 3, .box_h = 3, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 24, .adv_w = 26, .box_w = 1, .box_h = 3, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 25, .adv_w = 43, .box_w = 3, .box_h = 2, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 26, .adv_w = 70, .box_w = 4, .box_h = 3, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 28, .adv_w = 70, .box_w = 4, .box_h = 3, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 30, .adv_w = 50, .box_w = 3, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 32, .adv_w = 50, .box_w = 3, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 34, .adv_w = 40, .box_w = 2, .box_h = 3, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 35, .adv_w = 40, .box_w = 2, .box_h = 3, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 36, .adv_w = 50, .box_w = 3, .box_h = 2, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 37, .adv_w = 50, .box_w = 3, .box_h = 2, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 38, .adv_w = 78, .box_w = 5, .box_h = 6, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 42, .adv_w = 81, .box_w = 5, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 46, .adv_w = 81, .box_w = 6, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 49, .adv_w = 78, .box_w = 5, .box_h = 6, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 53, .adv_w = 78, .box_w = 5, .box_h = 6, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 57, .adv_w = 78, .box_w = 5, .box_h = 6, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 61, .adv_w = 80, .box_w = 6, .box_h = 4, .ofs_x = -1, .ofs_y = 0},
    {.bitmap_index = 64, .adv_w = 80, .box_w = 5, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 67, .adv_w = 80, .box_w = 5, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 71, .adv_w = 80, .box_w = 5, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 75, .adv_w = 80, .box_w = 5, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 79, .adv_w = 80, .box_w = 5, .box_h = 5, .ofs_x = 0, .ofs_y = 0}
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
const lv_font_t font_Symbols_5 = {
#else
lv_font_t font_Symbols_5 = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 6,          /*The maximum line height required by the font*/
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



#endif /*#if FONT_SYMBOLS_5*/

