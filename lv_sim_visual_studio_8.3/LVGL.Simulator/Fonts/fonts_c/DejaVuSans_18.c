/*******************************************************************************
 * Size: 18 px
 * Bpp: 1
 * Opts: 
 ******************************************************************************/

#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include <lvgl.h>
#endif

#ifndef DEJAVUSANS_18
#define DEJAVUSANS_18 1
#endif

#if DEJAVUSANS_18

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0021 "!" */
    0xff, 0xff, 0xc3, 0xc0,

    /* U+0025 "%" */
    0x78, 0x11, 0x98, 0x43, 0x30, 0x86, 0x62, 0xc,
    0xc8, 0x19, 0x90, 0x1e, 0x4f, 0x1, 0x33, 0x2,
    0x66, 0x8, 0xcc, 0x21, 0x98, 0x43, 0x31, 0x3,
    0xc0,

    /* U+002C "," */
    0x6d, 0x60,

    /* U+002D "-" */
    0xf8,

    /* U+002E "." */
    0xf0,

    /* U+003A ":" */
    0xf0, 0x3, 0xc0,

    /* U+003F "?" */
    0xfd, 0x1c, 0x18, 0x30, 0xe3, 0x8e, 0x18, 0x30,
    0x60, 0x1, 0x83, 0x0,

    /* U+0041 "A" */
    0x6, 0x0, 0x70, 0xd, 0x0, 0x98, 0x19, 0x81,
    0x88, 0x10, 0xc3, 0xc, 0x3f, 0xc6, 0x6, 0x60,
    0x24, 0x3, 0xc0, 0x30,

    /* U+0042 "B" */
    0xfe, 0x61, 0xb0, 0x78, 0x3c, 0x1e, 0x1b, 0xf9,
    0x86, 0xc1, 0xe0, 0xf0, 0x78, 0x6f, 0xe0,

    /* U+0043 "C" */
    0xf, 0xc6, 0xd, 0x80, 0xb0, 0xc, 0x1, 0x80,
    0x30, 0x6, 0x0, 0xc0, 0xc, 0x1, 0x80, 0x98,
    0x31, 0xfc,

    /* U+0044 "D" */
    0xfe, 0x18, 0x33, 0x3, 0x60, 0x7c, 0x7, 0x80,
    0xf0, 0x1e, 0x3, 0xc0, 0x78, 0xf, 0x3, 0x60,
    0xcf, 0xe0,

    /* U+0045 "E" */
    0xff, 0xe0, 0x30, 0x18, 0xc, 0x6, 0x3, 0xfd,
    0x80, 0xc0, 0x60, 0x30, 0x18, 0xf, 0xf8,

    /* U+0046 "F" */
    0xff, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xfe, 0xc0,
    0xc0, 0xc0, 0xc0, 0xc0, 0xc0,

    /* U+0047 "G" */
    0xf, 0xe3, 0x83, 0x60, 0x16, 0x0, 0xc0, 0xc,
    0x0, 0xc1, 0xfc, 0x3, 0xc0, 0x36, 0x3, 0x60,
    0x33, 0x7, 0xf, 0xe0,

    /* U+0048 "H" */
    0xc0, 0xf0, 0x3c, 0xf, 0x3, 0xc0, 0xf0, 0x3f,
    0xff, 0x3, 0xc0, 0xf0, 0x3c, 0xf, 0x3, 0xc0,
    0xc0,

    /* U+0049 "I" */
    0xff, 0xff, 0xff, 0xc0,

    /* U+004A "J" */
    0x18, 0xc6, 0x31, 0x8c, 0x63, 0x18, 0xc6, 0x31,
    0x8c, 0x66, 0xe0,

    /* U+004B "K" */
    0xc1, 0xd8, 0x73, 0x1c, 0x66, 0xd, 0x81, 0xe0,
    0x3c, 0x6, 0xc0, 0xcc, 0x18, 0xc3, 0xc, 0x60,
    0xcc, 0xc,

    /* U+004C "L" */
    0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0,
    0xc0, 0xc0, 0xc0, 0xc0, 0xff,

    /* U+004D "M" */
    0xe0, 0x7e, 0x7, 0xf0, 0xfd, 0xb, 0xd0, 0xbd,
    0x9b, 0xc9, 0x3c, 0xf3, 0xcf, 0x3c, 0x63, 0xc6,
    0x3c, 0x3, 0xc0, 0x30,

    /* U+004E "N" */
    0xe0, 0xf8, 0x3f, 0xf, 0x43, 0xd8, 0xf2, 0x3c,
    0xcf, 0x13, 0xc6, 0xf0, 0xbc, 0x3f, 0x7, 0xc1,
    0xc0,

    /* U+004F "O" */
    0x1f, 0x83, 0xc, 0x60, 0x66, 0x6, 0xc0, 0x3c,
    0x3, 0xc0, 0x3c, 0x3, 0xc0, 0x36, 0x6, 0x60,
    0x63, 0xc, 0x1f, 0x80,

    /* U+0050 "P" */
    0xfe, 0x61, 0xb0, 0x78, 0x3c, 0x1e, 0xf, 0xd,
    0xfc, 0xc0, 0x60, 0x30, 0x18, 0xc, 0x0,

    /* U+0051 "Q" */
    0x1f, 0x83, 0xc, 0x60, 0x66, 0x6, 0xc0, 0x3c,
    0x3, 0xc0, 0x3c, 0x3, 0xc0, 0x36, 0x6, 0x60,
    0x63, 0xc, 0x1f, 0x0, 0x18, 0x0, 0xc0,

    /* U+0052 "R" */
    0xfe, 0x18, 0x63, 0x6, 0x60, 0xcc, 0x19, 0x87,
    0x3f, 0xc6, 0x18, 0xc1, 0x18, 0x33, 0x2, 0x60,
    0x6c, 0x4,

    /* U+0053 "S" */
    0x3f, 0x30, 0xb0, 0x18, 0xe, 0x7, 0xe1, 0xfc,
    0xf, 0x1, 0x80, 0xc0, 0x78, 0x6f, 0xe0,

    /* U+0054 "T" */
    0xff, 0xe0, 0xc0, 0x18, 0x3, 0x0, 0x60, 0xc,
    0x1, 0x80, 0x30, 0x6, 0x0, 0xc0, 0x18, 0x3,
    0x0, 0x60,

    /* U+0055 "U" */
    0xc0, 0xf0, 0x3c, 0xf, 0x3, 0xc0, 0xf0, 0x3c,
    0xf, 0x3, 0xc0, 0xf0, 0x3c, 0xd, 0x86, 0x3f,
    0x0,

    /* U+0056 "V" */
    0xc0, 0x36, 0x3, 0x60, 0x66, 0x6, 0x30, 0x43,
    0xc, 0x10, 0xc1, 0x98, 0x19, 0x80, 0xd8, 0xf,
    0x0, 0x70, 0x6, 0x0,

    /* U+0057 "W" */
    0xc1, 0x83, 0xc1, 0x83, 0xc3, 0xc3, 0xc2, 0xc2,
    0x62, 0x46, 0x62, 0x46, 0x66, 0x66, 0x66, 0x64,
    0x34, 0x2c, 0x34, 0x2c, 0x3c, 0x3c, 0x1c, 0x38,
    0x18, 0x18,

    /* U+0058 "X" */
    0xc0, 0xcc, 0x10, 0xc6, 0x19, 0x81, 0xa0, 0x1c,
    0x3, 0x0, 0xf0, 0x13, 0x6, 0x21, 0x86, 0x20,
    0x6c, 0x4,

    /* U+0059 "Y" */
    0x60, 0x66, 0x6, 0x30, 0xc1, 0x98, 0x19, 0x80,
    0xf0, 0x6, 0x0, 0x60, 0x6, 0x0, 0x60, 0x6,
    0x0, 0x60, 0x6, 0x0,

    /* U+005A "Z" */
    0xff, 0xe0, 0x1c, 0x3, 0x0, 0xc0, 0x30, 0xc,
    0x3, 0x80, 0x60, 0x18, 0x6, 0x1, 0x80, 0x70,
    0xf, 0xfe,

    /* U+0061 "a" */
    0x7c, 0x46, 0x3, 0x3, 0x7f, 0xe3, 0xc3, 0xc3,
    0xc7, 0x7b,

    /* U+0062 "b" */
    0xc0, 0x60, 0x30, 0x18, 0xd, 0xe7, 0x1b, 0x7,
    0x83, 0xc1, 0xe0, 0xf0, 0x78, 0x3e, 0x36, 0xf0,

    /* U+0063 "c" */
    0x1f, 0x71, 0xe0, 0xc0, 0xc0, 0xc0, 0xc0, 0x60,
    0x61, 0x1f,

    /* U+0064 "d" */
    0x1, 0x80, 0xc0, 0x60, 0x33, 0xdb, 0x1f, 0x7,
    0x83, 0xc1, 0xe0, 0xf0, 0x78, 0x36, 0x39, 0xec,

    /* U+0065 "e" */
    0x3e, 0x31, 0xb0, 0x78, 0x3f, 0xfe, 0x3, 0x1,
    0xc0, 0x61, 0x8f, 0x80,

    /* U+0066 "f" */
    0x3e, 0xc1, 0x83, 0xf, 0xcc, 0x18, 0x30, 0x60,
    0xc1, 0x83, 0x6, 0xc, 0x0,

    /* U+0067 "g" */
    0x3d, 0xb1, 0xf0, 0x78, 0x3c, 0x1e, 0xf, 0x7,
    0x83, 0x63, 0x9e, 0xc0, 0x60, 0x34, 0x33, 0xf0,

    /* U+0068 "h" */
    0xc0, 0xc0, 0xc0, 0xc0, 0xde, 0xe6, 0xc3, 0xc3,
    0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3,

    /* U+0069 "i" */
    0xf0, 0xff, 0xff, 0xf0,

    /* U+006A "j" */
    0x33, 0x0, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33,
    0x3e,

    /* U+006B "k" */
    0xc0, 0x60, 0x30, 0x18, 0xc, 0x36, 0x33, 0x31,
    0xb0, 0xf0, 0x7c, 0x37, 0x19, 0xcc, 0x76, 0x1c,

    /* U+006C "l" */
    0xff, 0xff, 0xff, 0xf0,

    /* U+006D "m" */
    0xde, 0x7b, 0x9a, 0x6c, 0x30, 0xf0, 0xc3, 0xc3,
    0xf, 0xc, 0x3c, 0x30, 0xf0, 0xc3, 0xc3, 0xf,
    0xc, 0x30,

    /* U+006E "n" */
    0xde, 0xe6, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3,
    0xc3, 0xc3,

    /* U+006F "o" */
    0x3e, 0x31, 0xb0, 0x78, 0x3c, 0x1e, 0xf, 0x7,
    0x83, 0x63, 0x1f, 0x0,

    /* U+0070 "p" */
    0xde, 0x71, 0xb0, 0x78, 0x3c, 0x1e, 0xf, 0x7,
    0x83, 0xe3, 0x6f, 0x30, 0x18, 0xc, 0x6, 0x0,

    /* U+0071 "q" */
    0x3d, 0xb1, 0xf0, 0x78, 0x3c, 0x1e, 0xf, 0x7,
    0x83, 0x63, 0x9e, 0xc0, 0x60, 0x30, 0x18, 0xc,

    /* U+0072 "r" */
    0xdf, 0x8c, 0x30, 0xc3, 0xc, 0x30, 0xc3, 0x0,

    /* U+0073 "s" */
    0x7e, 0xc0, 0xc0, 0xe0, 0xfc, 0x3f, 0x3, 0x3,
    0x87, 0xfc,

    /* U+0074 "t" */
    0x61, 0x86, 0x3f, 0x61, 0x86, 0x18, 0x61, 0x86,
    0x18, 0x3c,

    /* U+0075 "u" */
    0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3,
    0xe7, 0x7b,

    /* U+0076 "v" */
    0x81, 0xe0, 0xf0, 0xcc, 0x66, 0x21, 0x30, 0xd8,
    0x68, 0x1c, 0xe, 0x0,

    /* U+0077 "w" */
    0xc6, 0x1e, 0x38, 0xf1, 0x44, 0x9a, 0x66, 0xd3,
    0x34, 0xd9, 0xa2, 0x87, 0x1c, 0x38, 0xe1, 0x87,
    0x0,

    /* U+0078 "x" */
    0xc1, 0xb1, 0x8d, 0x87, 0x81, 0xc0, 0xe0, 0xd8,
    0xcc, 0x63, 0x60, 0xc0,

    /* U+0079 "y" */
    0xc0, 0xd0, 0x66, 0x19, 0x84, 0x33, 0xc, 0xc1,
    0x20, 0x78, 0x1c, 0x3, 0x0, 0xc0, 0x20, 0x18,
    0x1c, 0x0,

    /* U+007A "z" */
    0xff, 0x3, 0x6, 0xc, 0x18, 0x18, 0x30, 0x60,
    0xc0, 0xff
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 115, .box_w = 2, .box_h = 13, .ofs_x = 3, .ofs_y = 0},
    {.bitmap_index = 4, .adv_w = 274, .box_w = 15, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 29, .adv_w = 92, .box_w = 3, .box_h = 4, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 31, .adv_w = 104, .box_w = 5, .box_h = 1, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 32, .adv_w = 92, .box_w = 2, .box_h = 2, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 33, .adv_w = 97, .box_w = 2, .box_h = 9, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 36, .adv_w = 153, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 48, .adv_w = 197, .box_w = 12, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 68, .adv_w = 198, .box_w = 9, .box_h = 13, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 83, .adv_w = 201, .box_w = 11, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 101, .adv_w = 222, .box_w = 11, .box_h = 13, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 119, .adv_w = 182, .box_w = 9, .box_h = 13, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 134, .adv_w = 166, .box_w = 8, .box_h = 13, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 147, .adv_w = 223, .box_w = 12, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 167, .adv_w = 217, .box_w = 10, .box_h = 13, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 184, .adv_w = 85, .box_w = 2, .box_h = 13, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 188, .adv_w = 85, .box_w = 5, .box_h = 17, .ofs_x = -1, .ofs_y = -4},
    {.bitmap_index = 199, .adv_w = 189, .box_w = 11, .box_h = 13, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 217, .adv_w = 160, .box_w = 8, .box_h = 13, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 230, .adv_w = 248, .box_w = 12, .box_h = 13, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 250, .adv_w = 215, .box_w = 10, .box_h = 13, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 267, .adv_w = 227, .box_w = 12, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 287, .adv_w = 174, .box_w = 9, .box_h = 13, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 302, .adv_w = 227, .box_w = 12, .box_h = 15, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 325, .adv_w = 200, .box_w = 11, .box_h = 13, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 343, .adv_w = 183, .box_w = 9, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 358, .adv_w = 176, .box_w = 11, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 376, .adv_w = 211, .box_w = 10, .box_h = 13, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 393, .adv_w = 197, .box_w = 12, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 413, .adv_w = 285, .box_w = 16, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 439, .adv_w = 197, .box_w = 11, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 457, .adv_w = 176, .box_w = 12, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 477, .adv_w = 197, .box_w = 11, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 495, .adv_w = 176, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 505, .adv_w = 183, .box_w = 9, .box_h = 14, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 521, .adv_w = 158, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 531, .adv_w = 183, .box_w = 9, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 547, .adv_w = 177, .box_w = 9, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 559, .adv_w = 101, .box_w = 7, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 572, .adv_w = 183, .box_w = 9, .box_h = 14, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 588, .adv_w = 183, .box_w = 8, .box_h = 14, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 602, .adv_w = 80, .box_w = 2, .box_h = 14, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 606, .adv_w = 80, .box_w = 4, .box_h = 18, .ofs_x = 0, .ofs_y = -4},
    {.bitmap_index = 615, .adv_w = 167, .box_w = 9, .box_h = 14, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 631, .adv_w = 80, .box_w = 2, .box_h = 14, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 635, .adv_w = 281, .box_w = 14, .box_h = 10, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 653, .adv_w = 183, .box_w = 8, .box_h = 10, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 663, .adv_w = 176, .box_w = 9, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 675, .adv_w = 183, .box_w = 9, .box_h = 14, .ofs_x = 2, .ofs_y = -4},
    {.bitmap_index = 691, .adv_w = 183, .box_w = 9, .box_h = 14, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 707, .adv_w = 118, .box_w = 6, .box_h = 10, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 715, .adv_w = 150, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 725, .adv_w = 113, .box_w = 6, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 735, .adv_w = 183, .box_w = 8, .box_h = 10, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 745, .adv_w = 170, .box_w = 9, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 757, .adv_w = 236, .box_w = 13, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 774, .adv_w = 170, .box_w = 9, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 786, .adv_w = 170, .box_w = 10, .box_h = 14, .ofs_x = 0, .ofs_y = -4},
    {.bitmap_index = 804, .adv_w = 151, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/

static const uint16_t unicode_list_0[] = {
    0x0, 0x4, 0xb, 0xc, 0xd, 0x19, 0x1e
};

/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] =
{
    {
        .range_start = 33, .range_length = 31, .glyph_id_start = 1,
        .unicode_list = unicode_list_0, .glyph_id_ofs_list = NULL, .list_length = 7, .type = LV_FONT_FMT_TXT_CMAP_SPARSE_TINY
    },
    {
        .range_start = 65, .range_length = 26, .glyph_id_start = 8,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    },
    {
        .range_start = 97, .range_length = 26, .glyph_id_start = 34,
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
    .cmap_num = 3,
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
const lv_font_t DejaVuSans_18 = {
#else
lv_font_t DejaVuSans_18 = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 18,          /*The maximum line height required by the font*/
    .base_line = 4,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = -1,
    .underline_thickness = 1,
#endif
    .dsc = &font_dsc           /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
};



#endif /*#if DEJAVUSANS_18*/

