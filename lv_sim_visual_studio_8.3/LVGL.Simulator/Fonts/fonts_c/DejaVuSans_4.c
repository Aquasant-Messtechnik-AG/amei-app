/*******************************************************************************
 * Size: 4 px
 * Bpp: 1
 * Opts: 
 ******************************************************************************/

#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include <lvgl.h>
#endif

#ifndef DEJAVUSANS_4
#define DEJAVUSANS_4 1
#endif

#if DEJAVUSANS_4

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " */
    0x0,

    /* U+0021 "!" */
    0xc0,

    /* U+0022 "\"" */
    0x80,

    /* U+0023 "#" */
    0x6f, 0x80,

    /* U+0024 "$" */
    0x6c,

    /* U+0025 "%" */
    0xaa, 0x60,

    /* U+0026 "&" */
    0x93, 0x0,

    /* U+0027 "'" */
    0x80,

    /* U+0028 "(" */
    0x40,

    /* U+0029 ")" */
    0x40,

    /* U+002A "*" */
    0xc0,

    /* U+002B "+" */
    0xe0,

    /* U+002C "," */
    0x80,

    /* U+002D "-" */
    0x80,

    /* U+002E "." */
    0x0,

    /* U+002F "/" */
    0x60,

    /* U+0030 "0" */
    0xd7, 0x0,

    /* U+0031 "1" */
    0xe0,

    /* U+0032 "2" */
    0x58,

    /* U+0033 "3" */
    0x54,

    /* U+0034 "4" */
    0x7c,

    /* U+0035 "5" */
    0xb4,

    /* U+0036 "6" */
    0xac,

    /* U+0037 "7" */
    0x50,

    /* U+0038 "8" */
    0xec,

    /* U+0039 "9" */
    0xd4,

    /* U+003A ":" */
    0x80,

    /* U+003B ";" */
    0xa0,

    /* U+003C "<" */
    0x5c,

    /* U+003D "=" */
    0xfc,

    /* U+003E ">" */
    0x4c,

    /* U+003F "?" */
    0x40,

    /* U+0040 "@" */
    0x69, 0xe6,

    /* U+0041 "A" */
    0x5b, 0x80,

    /* U+0042 "B" */
    0xfc,

    /* U+0043 "C" */
    0xf3, 0x80,

    /* U+0044 "D" */
    0xd7, 0x0,

    /* U+0045 "E" */
    0xb8,

    /* U+0046 "F" */
    0xb8,

    /* U+0047 "G" */
    0xf7, 0x80,

    /* U+0048 "H" */
    0xbe, 0x80,

    /* U+0049 "I" */
    0xe0,

    /* U+004A "J" */
    0xf0,

    /* U+004B "K" */
    0xd3, 0x0,

    /* U+004C "L" */
    0xa8,

    /* U+004D "M" */
    0xb7, 0x80,

    /* U+004E "N" */
    0xbe, 0x80,

    /* U+004F "O" */
    0xd7, 0x0,

    /* U+0050 "P" */
    0xf0,

    /* U+0051 "Q" */
    0xd7, 0x0,

    /* U+0052 "R" */
    0xda, 0x0,

    /* U+0053 "S" */
    0x94,

    /* U+0054 "T" */
    0x49, 0x0,

    /* U+0055 "U" */
    0xb7, 0x80,

    /* U+0056 "V" */
    0xb9, 0x0,

    /* U+0057 "W" */
    0xde, 0xa0,

    /* U+0058 "X" */
    0xa, 0x0,

    /* U+0059 "Y" */
    0x9, 0x0,

    /* U+005A "Z" */
    0x4b, 0x0,

    /* U+005B "[" */
    0xf0,

    /* U+005C "\\" */
    0xc0,

    /* U+005D "]" */
    0xf0,

    /* U+005E "^" */
    0x40,

    /* U+005F "_" */
    0xc0,

    /* U+0060 "`" */
    0x80,

    /* U+0061 "a" */
    0x70,

    /* U+0062 "b" */
    0x9f, 0x80,

    /* U+0063 "c" */
    0xa0,

    /* U+0064 "d" */
    0x3f, 0x80,

    /* U+0065 "e" */
    0xe0,

    /* U+0066 "f" */
    0xe0,

    /* U+0067 "g" */
    0xf5, 0x80,

    /* U+0068 "h" */
    0xbc,

    /* U+0069 "i" */
    0x60,

    /* U+006A "j" */
    0x70,

    /* U+006B "k" */
    0xbc,

    /* U+006C "l" */
    0xe0,

    /* U+006D "m" */
    0xfc,

    /* U+006E "n" */
    0xf0,

    /* U+006F "o" */
    0xfc,

    /* U+0070 "p" */
    0xf7, 0x0,

    /* U+0071 "q" */
    0xf5, 0x80,

    /* U+0072 "r" */
    0xa0,

    /* U+0073 "s" */
    0x90,

    /* U+0074 "t" */
    0xe0,

    /* U+0075 "u" */
    0xf0,

    /* U+0076 "v" */
    0x90,

    /* U+0077 "w" */
    0xd4,

    /* U+0078 "x" */
    0x50,

    /* U+0079 "y" */
    0x90,

    /* U+007A "z" */
    0x60,

    /* U+007B "{" */
    0xe0,

    /* U+007C "|" */
    0xf0,

    /* U+007D "}" */
    0xe0,

    /* U+007E "~" */
    0xe0
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 20, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1, .adv_w = 26, .box_w = 1, .box_h = 3, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2, .adv_w = 29, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 3, .adv_w = 54, .box_w = 3, .box_h = 3, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 5, .adv_w = 41, .box_w = 2, .box_h = 4, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 6, .adv_w = 61, .box_w = 4, .box_h = 3, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 8, .adv_w = 50, .box_w = 3, .box_h = 3, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 10, .adv_w = 18, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 11, .adv_w = 25, .box_w = 1, .box_h = 3, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 12, .adv_w = 25, .box_w = 1, .box_h = 3, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 13, .adv_w = 32, .box_w = 2, .box_h = 2, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 14, .adv_w = 54, .box_w = 3, .box_h = 2, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 15, .adv_w = 20, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 16, .adv_w = 23, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 17, .adv_w = 20, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 18, .adv_w = 22, .box_w = 1, .box_h = 3, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 19, .adv_w = 41, .box_w = 3, .box_h = 3, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 21, .adv_w = 41, .box_w = 1, .box_h = 3, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 22, .adv_w = 41, .box_w = 2, .box_h = 3, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 23, .adv_w = 41, .box_w = 2, .box_h = 3, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 24, .adv_w = 41, .box_w = 2, .box_h = 3, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 25, .adv_w = 41, .box_w = 2, .box_h = 3, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 26, .adv_w = 41, .box_w = 2, .box_h = 3, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 27, .adv_w = 41, .box_w = 2, .box_h = 3, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 28, .adv_w = 41, .box_w = 2, .box_h = 3, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 29, .adv_w = 41, .box_w = 2, .box_h = 3, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 30, .adv_w = 22, .box_w = 1, .box_h = 2, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 31, .adv_w = 22, .box_w = 1, .box_h = 3, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 32, .adv_w = 54, .box_w = 3, .box_h = 2, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 33, .adv_w = 54, .box_w = 3, .box_h = 2, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 34, .adv_w = 54, .box_w = 3, .box_h = 2, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 35, .adv_w = 34, .box_w = 2, .box_h = 3, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 36, .adv_w = 64, .box_w = 4, .box_h = 4, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 38, .adv_w = 44, .box_w = 3, .box_h = 3, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 40, .adv_w = 44, .box_w = 2, .box_h = 3, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 41, .adv_w = 45, .box_w = 3, .box_h = 3, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 43, .adv_w = 49, .box_w = 3, .box_h = 3, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 45, .adv_w = 40, .box_w = 2, .box_h = 3, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 46, .adv_w = 37, .box_w = 2, .box_h = 3, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 47, .adv_w = 50, .box_w = 3, .box_h = 3, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 49, .adv_w = 48, .box_w = 3, .box_h = 3, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 51, .adv_w = 19, .box_w = 1, .box_h = 3, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 52, .adv_w = 19, .box_w = 1, .box_h = 4, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 53, .adv_w = 42, .box_w = 3, .box_h = 3, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 55, .adv_w = 36, .box_w = 2, .box_h = 3, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 56, .adv_w = 55, .box_w = 3, .box_h = 3, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 58, .adv_w = 48, .box_w = 3, .box_h = 3, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 60, .adv_w = 50, .box_w = 3, .box_h = 3, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 62, .adv_w = 39, .box_w = 2, .box_h = 3, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 63, .adv_w = 50, .box_w = 3, .box_h = 4, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 65, .adv_w = 44, .box_w = 3, .box_h = 3, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 67, .adv_w = 41, .box_w = 2, .box_h = 3, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 68, .adv_w = 39, .box_w = 3, .box_h = 3, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 70, .adv_w = 47, .box_w = 3, .box_h = 3, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 72, .adv_w = 44, .box_w = 3, .box_h = 3, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 74, .adv_w = 63, .box_w = 4, .box_h = 3, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 76, .adv_w = 44, .box_w = 3, .box_h = 3, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 78, .adv_w = 39, .box_w = 3, .box_h = 3, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 80, .adv_w = 44, .box_w = 3, .box_h = 3, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 82, .adv_w = 25, .box_w = 1, .box_h = 4, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 83, .adv_w = 22, .box_w = 1, .box_h = 3, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 84, .adv_w = 25, .box_w = 1, .box_h = 4, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 85, .adv_w = 54, .box_w = 3, .box_h = 1, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 86, .adv_w = 32, .box_w = 2, .box_h = 1, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 87, .adv_w = 32, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 88, .adv_w = 39, .box_w = 2, .box_h = 2, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 89, .adv_w = 41, .box_w = 3, .box_h = 3, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 91, .adv_w = 35, .box_w = 2, .box_h = 2, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 92, .adv_w = 41, .box_w = 3, .box_h = 3, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 94, .adv_w = 39, .box_w = 2, .box_h = 2, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 95, .adv_w = 23, .box_w = 1, .box_h = 3, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 96, .adv_w = 41, .box_w = 3, .box_h = 3, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 98, .adv_w = 41, .box_w = 2, .box_h = 3, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 99, .adv_w = 18, .box_w = 1, .box_h = 3, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 100, .adv_w = 18, .box_w = 1, .box_h = 4, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 101, .adv_w = 37, .box_w = 2, .box_h = 3, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 102, .adv_w = 18, .box_w = 1, .box_h = 3, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 103, .adv_w = 62, .box_w = 3, .box_h = 2, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 104, .adv_w = 41, .box_w = 2, .box_h = 2, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 105, .adv_w = 39, .box_w = 3, .box_h = 2, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 106, .adv_w = 41, .box_w = 3, .box_h = 3, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 108, .adv_w = 41, .box_w = 3, .box_h = 3, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 110, .adv_w = 26, .box_w = 2, .box_h = 2, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 111, .adv_w = 33, .box_w = 2, .box_h = 2, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 112, .adv_w = 25, .box_w = 1, .box_h = 3, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 113, .adv_w = 41, .box_w = 2, .box_h = 2, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 114, .adv_w = 38, .box_w = 2, .box_h = 2, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 115, .adv_w = 52, .box_w = 3, .box_h = 2, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 116, .adv_w = 38, .box_w = 2, .box_h = 2, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 117, .adv_w = 38, .box_w = 2, .box_h = 3, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 118, .adv_w = 34, .box_w = 2, .box_h = 2, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 119, .adv_w = 41, .box_w = 1, .box_h = 4, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 120, .adv_w = 22, .box_w = 1, .box_h = 4, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 121, .adv_w = 41, .box_w = 1, .box_h = 4, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 122, .adv_w = 54, .box_w = 3, .box_h = 1, .ofs_x = 0, .ofs_y = 1}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/



/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] =
{
    {
        .range_start = 32, .range_length = 95, .glyph_id_start = 1,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
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
const lv_font_t DejaVuSans_4 = {
#else
lv_font_t DejaVuSans_4 = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 4,          /*The maximum line height required by the font*/
    .base_line = 1,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = 0,
    .underline_thickness = 0,
#endif
    .dsc = &font_dsc           /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
};



#endif /*#if DEJAVUSANS_4*/

