/*******************************************************************************
 * Size: 6 px
 * Bpp: 1
 * Opts: 
 ******************************************************************************/

#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "lvgl.h"
#endif

#ifndef FONT_SYMBOLS_6
#define FONT_SYMBOLS_6 1
#endif

#if FONT_SYMBOLS_6

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
    0xd6, 0xe0,

    /* U+0031 "1" */
    0x55,

    /* U+0032 "2" */
    0xe5, 0x60,

    /* U+0033 "3" */
    0xe8, 0xe0,

    /* U+0034 "4" */
    0x2f, 0x90,

    /* U+0035 "5" */
    0xd8, 0xe0,

    /* U+0036 "6" */
    0x7a, 0xa0,

    /* U+0037 "7" */
    0x69, 0x40,

    /* U+0038 "8" */
    0xea, 0xd6,

    /* U+0039 "9" */
    0x69, 0x7e,

    /* U+0061 "a" */
    0xf7, 0x80,

    /* U+0063 "c" */
    0x71, 0x80,

    /* U+0064 "d" */
    0x3e, 0xf0,

    /* U+0066 "f" */
    0xaa,

    /* U+0078 "x" */
    0xaa, 0x80,

    /* U+F100 "" */
    0x2a, 0x94, 0x50,

    /* U+F101 "" */
    0x92, 0xdf, 0x20,

    /* U+F102 "" */
    0x6, 0x96, 0x90,

    /* U+F103 "" */
    0x9f, 0x4f, 0x60,

    /* U+F104 "" */
    0x2b, 0x10,

    /* U+F105 "" */
    0x89, 0xc0,

    /* U+F106 "" */
    0x69,

    /* U+F107 "" */
    0xf6,

    /* U+F498 "" */
    0xfe, 0x18, 0x69, 0x87, 0xf0,

    /* U+F499 "" */
    0xfe, 0xb9, 0x71, 0xc1, 0x80, 0x0,

    /* U+F49A "" */
    0xfe, 0x1b, 0x94, 0x50, 0x80,

    /* U+F49B "" */
    0xfe, 0x1b, 0x6d, 0x87, 0xf0,

    /* U+F49C "" */
    0xfe, 0x18, 0x69, 0x87, 0xf0,

    /* U+F49D "" */
    0xfe, 0x18, 0x61, 0x87, 0xf0,

    /* U+F4C5 "" */
    0x11, 0xab, 0x5e,

    /* U+F4C6 "" */
    0x20, 0xc5, 0xa6, 0xfc,

    /* U+F4C7 "" */
    0xfd, 0xe8, 0x9c, 0x50, 0x80,

    /* U+F4C8 "" */
    0x7a, 0x2b, 0x76, 0x78,

    /* U+F4C9 "" */
    0xfe, 0x3d, 0x69, 0xfc,

    /* U+F4CA "" */
    0xfe, 0x18, 0x61, 0xfc
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 38, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1, .adv_w = 41, .box_w = 2, .box_h = 1, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 2, .adv_w = 22, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 3, .adv_w = 58, .box_w = 3, .box_h = 4, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 5, .adv_w = 63, .box_w = 2, .box_h = 4, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 6, .adv_w = 58, .box_w = 3, .box_h = 4, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 8, .adv_w = 56, .box_w = 3, .box_h = 4, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 10, .adv_w = 59, .box_w = 3, .box_h = 4, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 12, .adv_w = 60, .box_w = 3, .box_h = 4, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 14, .adv_w = 58, .box_w = 3, .box_h = 4, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 16, .adv_w = 58, .box_w = 3, .box_h = 4, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 18, .adv_w = 58, .box_w = 4, .box_h = 4, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 20, .adv_w = 57, .box_w = 4, .box_h = 4, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 22, .adv_w = 55, .box_w = 3, .box_h = 3, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 24, .adv_w = 50, .box_w = 3, .box_h = 3, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 26, .adv_w = 55, .box_w = 3, .box_h = 4, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 28, .adv_w = 32, .box_w = 2, .box_h = 4, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 29, .adv_w = 51, .box_w = 3, .box_h = 3, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 31, .adv_w = 84, .box_w = 5, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 34, .adv_w = 84, .box_w = 5, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 37, .adv_w = 60, .box_w = 4, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 40, .adv_w = 60, .box_w = 4, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 43, .adv_w = 48, .box_w = 3, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 45, .adv_w = 48, .box_w = 3, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 47, .adv_w = 60, .box_w = 4, .box_h = 2, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 48, .adv_w = 60, .box_w = 4, .box_h = 2, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 49, .adv_w = 94, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 54, .adv_w = 98, .box_w = 7, .box_h = 6, .ofs_x = -1, .ofs_y = -1},
    {.bitmap_index = 60, .adv_w = 97, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 65, .adv_w = 94, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 70, .adv_w = 94, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 75, .adv_w = 94, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 80, .adv_w = 96, .box_w = 6, .box_h = 4, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 83, .adv_w = 96, .box_w = 6, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 87, .adv_w = 96, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 92, .adv_w = 96, .box_w = 6, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 96, .adv_w = 96, .box_w = 6, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 100, .adv_w = 96, .box_w = 6, .box_h = 5, .ofs_x = 0, .ofs_y = 0}
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
const lv_font_t font_Symbols_6 = {
#else
lv_font_t font_Symbols_6 = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 7,          /*The maximum line height required by the font*/
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



#endif /*#if FONT_SYMBOLS_6*/

