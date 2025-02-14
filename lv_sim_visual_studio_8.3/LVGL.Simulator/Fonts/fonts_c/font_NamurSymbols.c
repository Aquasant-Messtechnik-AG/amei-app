/*******************************************************************************
 * Size: 12 px
 * Bpp: 1
 * Opts: 
 ******************************************************************************/

#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include <lvgl.h>
#endif

#ifndef FONT_NAMURSYMBOLS
#define FONT_NAMURSYMBOLS 1
#endif

#if FONT_NAMURSYMBOLS

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+002D "-" */
    0xe0,

    /* U+0030 "0" */
    0x79, 0x28, 0x61, 0x86, 0x18, 0x61, 0x49, 0xe0,

    /* U+0034 "4" */
    0x8, 0x61, 0x8a, 0x29, 0x28, 0xbf, 0x8, 0x20,

    /* U+0035 "5" */
    0xfc, 0x21, 0xf, 0x4c, 0x21, 0x9b, 0x80,

    /* U+0061 "a" */
    0x77, 0x38, 0x61, 0x87, 0x37, 0x40,

    /* U+0063 "c" */
    0x7e, 0x61, 0x8, 0x65, 0xe0,

    /* U+0066 "f" */
    0x74, 0x4e, 0x44, 0x44, 0x44,

    /* U+0078 "x" */
    0x45, 0x23, 0x4, 0x39, 0x2c, 0x40,

    /* U+F4C5 "" */
    0x2, 0x0, 0xd0, 0x10, 0x82, 0x4, 0x40, 0x2b,
    0xfd, 0xbe, 0x24, 0x4, 0x20, 0x81, 0x10, 0xa,
    0x0, 0x40,

    /* U+F4C6 "" */
    0x4, 0x0, 0xa0, 0xa, 0x1, 0x10, 0x26, 0x82,
    0x28, 0x44, 0x44, 0x2, 0x80, 0x2f, 0xff,

    /* U+F4C7 "" */
    0xff, 0xe8, 0x42, 0x46, 0x44, 0x64, 0x24, 0x81,
    0x48, 0x15, 0x0, 0xe0, 0x6, 0x0, 0x0,

    /* U+F4C8 "" */
    0x1f, 0x82, 0x6, 0x40, 0x29, 0x11, 0x8a, 0x18,
    0x61, 0x8b, 0x19, 0x12, 0x40, 0x22, 0x4, 0x1f,
    0x80,

    /* U+F4C9 "" */
    0xff, 0xf8, 0x1, 0x80, 0x18, 0x9, 0x81, 0x18,
    0x21, 0x8c, 0x18, 0xc1, 0x80, 0x18, 0x1, 0x80,
    0x1f, 0xff,

    /* U+F4CA "" */
    0xff, 0xf8, 0x1, 0x80, 0x18, 0x1, 0x80, 0x18,
    0x1, 0x80, 0x18, 0x1, 0x80, 0x18, 0x1, 0x80,
    0x1f, 0xff
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 82, .box_w = 3, .box_h = 1, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 1, .adv_w = 115, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 9, .adv_w = 118, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 17, .adv_w = 121, .box_w = 5, .box_h = 10, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 24, .adv_w = 110, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 30, .adv_w = 100, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 35, .adv_w = 63, .box_w = 4, .box_h = 10, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 40, .adv_w = 103, .box_w = 6, .box_h = 7, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 46, .adv_w = 192, .box_w = 12, .box_h = 12, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 64, .adv_w = 192, .box_w = 12, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 79, .adv_w = 192, .box_w = 12, .box_h = 10, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 94, .adv_w = 192, .box_w = 12, .box_h = 11, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 111, .adv_w = 192, .box_w = 12, .box_h = 12, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 129, .adv_w = 192, .box_w = 12, .box_h = 12, .ofs_x = 0, .ofs_y = -1}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/

static const uint16_t unicode_list_0[] = {
    0x0, 0x3, 0x7, 0x8, 0x34, 0x36, 0x39, 0x4b,
    0xf498, 0xf499, 0xf49a, 0xf49b, 0xf49c, 0xf49d
};

/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] =
{
    {
        .range_start = 45, .range_length = 62622, .glyph_id_start = 1,
        .unicode_list = unicode_list_0, .glyph_id_ofs_list = NULL, .list_length = 14, .type = LV_FONT_FMT_TXT_CMAP_SPARSE_TINY
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
const lv_font_t font_NamurSymbols = {
#else
lv_font_t font_NamurSymbols = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 13,          /*The maximum line height required by the font*/
    .base_line = 2,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = -4,
    .underline_thickness = 1,
#endif
    .dsc = &font_dsc           /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
};



#endif /*#if FONT_NAMURSYMBOLS*/

