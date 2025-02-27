/*******************************************************************************
 * Size: 30 px
 * Bpp: 1
 * Opts: 
 ******************************************************************************/

#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "lvgl.h"
#endif

#ifndef FONT_SYMBOLS_30
#define FONT_SYMBOLS_30 1
#endif

#if FONT_SYMBOLS_30

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " */
    0x0,

    /* U+002D "-" */
    0xff, 0xff, 0xc0,

    /* U+002E "." */
    0xff, 0x80,

    /* U+0030 "0" */
    0x7, 0xc0, 0x3f, 0xe0, 0xe0, 0xe3, 0x80, 0xc6,
    0x0, 0xcc, 0x1, 0xb0, 0x1, 0xe0, 0x3, 0xc0,
    0x7, 0x80, 0xf, 0x0, 0x1e, 0x0, 0x3c, 0x0,
    0x78, 0x0, 0xf0, 0x1, 0xe0, 0x7, 0x60, 0xc,
    0xc0, 0x19, 0xc0, 0x71, 0xc1, 0xc1, 0xff, 0x0,
    0xf8, 0x0,

    /* U+0031 "1" */
    0x6, 0x1c, 0xfb, 0xfe, 0x70, 0xc1, 0x83, 0x6,
    0xc, 0x18, 0x30, 0x60, 0xc1, 0x83, 0x6, 0xc,
    0x18, 0x30, 0x60, 0xc0,

    /* U+0032 "2" */
    0xf, 0xc0, 0x7f, 0xe1, 0xe0, 0xe3, 0x0, 0xe0,
    0x0, 0xc0, 0x1, 0x80, 0x3, 0x0, 0x6, 0x0,
    0x18, 0x0, 0x30, 0x0, 0xc0, 0x3, 0x80, 0xe,
    0x0, 0x38, 0x0, 0xe0, 0x3, 0x80, 0xf, 0x0,
    0x3c, 0x0, 0x70, 0x1, 0xc0, 0x7, 0xff, 0xef,
    0xff, 0xc0,

    /* U+0033 "3" */
    0xf, 0xc1, 0xff, 0x8f, 0x7, 0x30, 0xe, 0x0,
    0x18, 0x0, 0x60, 0x1, 0x80, 0x6, 0x0, 0x30,
    0x1, 0xc0, 0xfe, 0x3, 0xfc, 0x0, 0x38, 0x0,
    0x60, 0x0, 0xc0, 0x3, 0x0, 0xc, 0x0, 0x3c,
    0x1, 0xfc, 0xe, 0x7f, 0xf0, 0x7f, 0x0,

    /* U+0034 "4" */
    0x0, 0x30, 0x0, 0x70, 0x0, 0x70, 0x0, 0xf0,
    0x1, 0xf0, 0x1, 0xb0, 0x3, 0x30, 0x7, 0x30,
    0x6, 0x30, 0xc, 0x30, 0x1c, 0x30, 0x38, 0x30,
    0x30, 0x30, 0x70, 0x30, 0xe0, 0x30, 0xff, 0xff,
    0xff, 0xff, 0x0, 0x30, 0x0, 0x30, 0x0, 0x30,
    0x0, 0x30, 0x0, 0x30,

    /* U+0035 "5" */
    0x7f, 0xf9, 0xff, 0xe6, 0x0, 0x18, 0x0, 0x60,
    0x1, 0x80, 0x6, 0x0, 0x18, 0x0, 0x67, 0xc1,
    0xff, 0xc7, 0x87, 0x98, 0x6, 0x40, 0x1c, 0x0,
    0x30, 0x0, 0xc0, 0x3, 0x0, 0xc, 0x0, 0x76,
    0x1, 0xbe, 0xe, 0x3f, 0xf0, 0x3f, 0x0,

    /* U+0036 "6" */
    0x7, 0xe0, 0x1f, 0xf8, 0x70, 0x79, 0x80, 0x37,
    0x0, 0xc, 0x0, 0x18, 0x0, 0x60, 0x0, 0xc7,
    0xe1, 0x9f, 0xf3, 0x70, 0xf7, 0x80, 0x6e, 0x0,
    0xfc, 0x0, 0xf8, 0x1, 0xf0, 0x3, 0x60, 0x6,
    0xc0, 0x1c, 0xc0, 0x31, 0xe1, 0xc1, 0xff, 0x0,
    0xfc, 0x0,

    /* U+0037 "7" */
    0xff, 0xff, 0xff, 0xf0, 0x1, 0xc0, 0x6, 0x0,
    0x38, 0x0, 0xc0, 0x7, 0x0, 0x18, 0x0, 0xe0,
    0x3, 0x0, 0x1c, 0x0, 0x60, 0x3, 0x80, 0xc,
    0x0, 0x70, 0x1, 0x80, 0xe, 0x0, 0x30, 0x1,
    0xc0, 0x6, 0x0, 0x38, 0x0, 0xc0, 0x0,

    /* U+0038 "8" */
    0x7, 0xe0, 0x3f, 0xf0, 0xe0, 0x73, 0x80, 0x76,
    0x0, 0x6c, 0x0, 0xd8, 0x1, 0xb0, 0x3, 0x30,
    0xc, 0x78, 0x78, 0x3f, 0xc0, 0xff, 0xc7, 0x3,
    0xcc, 0x1, 0xf0, 0x1, 0xe0, 0x3, 0xc0, 0x7,
    0x80, 0xd, 0x80, 0x33, 0x80, 0xe3, 0xff, 0x81,
    0xfc, 0x0,

    /* U+0039 "9" */
    0xf, 0xc0, 0x3f, 0xe0, 0xe1, 0xe3, 0x0, 0xce,
    0x0, 0xd8, 0x1, 0xb0, 0x3, 0xe0, 0x7, 0xc0,
    0xf, 0xc0, 0x1d, 0x80, 0x7b, 0xc3, 0xb3, 0xfe,
    0x61, 0xf8, 0xc0, 0x1, 0x80, 0x6, 0x0, 0xc,
    0x0, 0x3b, 0x0, 0x67, 0x83, 0x87, 0xfe, 0x1,
    0xf8, 0x0,

    /* U+0061 "a" */
    0xf, 0x8c, 0x7f, 0xb3, 0x87, 0xd8, 0x7, 0x60,
    0x1f, 0x0, 0x3c, 0x0, 0xf0, 0x3, 0xc0, 0xf,
    0x0, 0x3c, 0x0, 0xd8, 0x7, 0x60, 0x1c, 0xe1,
    0xf3, 0xfe, 0xc3, 0xe3,

    /* U+0063 "c" */
    0xf, 0xc1, 0xff, 0x38, 0x76, 0x0, 0x60, 0xc,
    0x0, 0xc0, 0xc, 0x0, 0xc0, 0xc, 0x0, 0xc0,
    0x6, 0x0, 0x60, 0x3, 0x87, 0x1f, 0xf0, 0xfc,

    /* U+0064 "d" */
    0x0, 0xc, 0x0, 0x30, 0x0, 0xc0, 0x3, 0x0,
    0xc, 0x0, 0x30, 0x0, 0xc3, 0xf3, 0x1f, 0xec,
    0xe1, 0xf6, 0x1, 0xd8, 0x7, 0xc0, 0xf, 0x0,
    0x3c, 0x0, 0xf0, 0x3, 0xc0, 0xf, 0x0, 0x36,
    0x1, 0xd8, 0x7, 0x38, 0x7c, 0x7f, 0xb0, 0xf8,
    0xc0,

    /* U+0066 "f" */
    0x7, 0xc3, 0xf1, 0xc0, 0x60, 0x18, 0x6, 0x1,
    0x83, 0xfe, 0xff, 0x86, 0x1, 0x80, 0x60, 0x18,
    0x6, 0x1, 0x80, 0x60, 0x18, 0x6, 0x1, 0x80,
    0x60, 0x18, 0x6, 0x1, 0x80,

    /* U+0078 "x" */
    0x70, 0xe, 0x38, 0x1c, 0x1c, 0x18, 0x1c, 0x38,
    0xe, 0x70, 0x7, 0xe0, 0x3, 0xc0, 0x3, 0xc0,
    0x3, 0xc0, 0x7, 0xe0, 0x6, 0x70, 0xe, 0x70,
    0x1c, 0x38, 0x38, 0x1c, 0x70, 0xe, 0x70, 0xe,

    /* U+F100 "" */
    0x0, 0x60, 0xc, 0x0, 0xf0, 0x1e, 0x1, 0xf8,
    0x3f, 0x3, 0xf0, 0x7f, 0x7, 0xe0, 0xfe, 0xf,
    0xc1, 0xfc, 0x1f, 0x83, 0xf8, 0x3f, 0x7, 0xf0,
    0x7f, 0xf, 0xe0, 0xfe, 0xf, 0xc0, 0x7f, 0xf,
    0xe0, 0x3f, 0x7, 0xf0, 0x1f, 0x83, 0xf8, 0xf,
    0xc1, 0xfc, 0x7, 0xe0, 0xfe, 0x3, 0xf0, 0x7f,
    0x1, 0xf8, 0x3f, 0x0, 0xf0, 0x1e, 0x0, 0x60,
    0xc,

    /* U+F101 "" */
    0x30, 0x7, 0x0, 0x78, 0xf, 0x80, 0xfc, 0xf,
    0x80, 0x7e, 0xf, 0xc0, 0x3f, 0x7, 0xe0, 0x1f,
    0x83, 0xf0, 0xf, 0xc1, 0xf8, 0x7, 0xe0, 0xfc,
    0x7, 0xf0, 0x7e, 0x3, 0xf8, 0x3f, 0x7, 0xf0,
    0x7e, 0x7, 0xe0, 0xfc, 0xf, 0xc1, 0xf8, 0x1f,
    0x83, 0xf0, 0x3f, 0x7, 0xe0, 0x7e, 0xf, 0xc0,
    0xfc, 0xf, 0x80, 0x78, 0xf, 0x80, 0x30, 0x7,
    0x0,

    /* U+F102 "" */
    0x0, 0xe0, 0x0, 0x3e, 0x0, 0xf, 0xe0, 0x3,
    0xfe, 0x0, 0xff, 0xe0, 0x3f, 0xfe, 0xf, 0xef,
    0xe3, 0xf8, 0xfe, 0xfe, 0xf, 0xff, 0x80, 0xff,
    0xe0, 0xf, 0x98, 0x20, 0xe0, 0xe, 0x0, 0x3,
    0xe0, 0x0, 0xfe, 0x0, 0x3f, 0xe0, 0xf, 0xfe,
    0x3, 0xf7, 0xe0, 0xfc, 0x7e, 0x3f, 0x7, 0xef,
    0xc0, 0x7f, 0xf0, 0x7, 0xdc, 0x0, 0x70,

    /* U+F103 "" */
    0x30, 0x1, 0x8f, 0x0, 0x7b, 0xf0, 0x1f, 0xff,
    0x7, 0xf7, 0xf1, 0xfc, 0x7f, 0x7f, 0x7, 0xff,
    0xc0, 0x7f, 0xf0, 0x7, 0xfc, 0x0, 0x7f, 0x0,
    0x7, 0xc0, 0x10, 0x70, 0x47, 0x80, 0x3d, 0xf8,
    0xf, 0xff, 0x83, 0xfb, 0xf8, 0xfe, 0x3f, 0xbf,
    0x83, 0xff, 0xe0, 0x3f, 0xf8, 0x3, 0xfe, 0x0,
    0x3f, 0x80, 0x3, 0xe0, 0x0, 0x38, 0x0,

    /* U+F104 "" */
    0x0, 0x60, 0x7, 0x80, 0x7e, 0x7, 0xe0, 0x7e,
    0x7, 0xe0, 0x7e, 0x7, 0xe0, 0x7f, 0x7, 0xf0,
    0x1f, 0xc0, 0x7e, 0x1, 0xf8, 0x7, 0xe0, 0x1f,
    0x80, 0x7e, 0x1, 0xf8, 0x7, 0x80, 0x18,

    /* U+F105 "" */
    0x30, 0x3, 0xc0, 0x3f, 0x0, 0xfc, 0x3, 0xf0,
    0xf, 0xc0, 0x3f, 0x0, 0xfc, 0x7, 0xf0, 0x1f,
    0xc1, 0xfc, 0xf, 0xc0, 0xfc, 0xf, 0xc0, 0xfc,
    0xf, 0xc0, 0xfc, 0x3, 0xc0, 0xc, 0x0,

    /* U+F106 "" */
    0x0, 0xe0, 0x0, 0x3e, 0x0, 0xf, 0xe0, 0x3,
    0xfe, 0x0, 0xff, 0xe0, 0x3f, 0xfe, 0xf, 0xef,
    0xe3, 0xf8, 0xfe, 0xfe, 0xf, 0xff, 0x80, 0xfd,
    0xe0, 0xf, 0x18, 0x0, 0x40,

    /* U+F107 "" */
    0x70, 0x1, 0xdf, 0x0, 0x7f, 0xf0, 0x1f, 0xff,
    0x7, 0xf7, 0xf1, 0xfc, 0x3f, 0x7e, 0x3, 0xff,
    0x80, 0x3f, 0xe0, 0x3, 0xf8, 0x0, 0x3e, 0x0,
    0x3, 0x80, 0x0, 0x20, 0x0,

    /* U+F498 "" */
    0xff, 0xff, 0xff, 0xf0, 0x0, 0x0, 0x6, 0x0,
    0x0, 0x0, 0xc0, 0x0, 0x0, 0x18, 0x0, 0x0,
    0x3, 0x0, 0x0, 0x0, 0x60, 0x0, 0x0, 0xc,
    0x0, 0x0, 0x1, 0x80, 0x0, 0x0, 0x30, 0x0,
    0x0, 0x6, 0x0, 0x0, 0x0, 0xc3, 0x80, 0x0,
    0x18, 0x40, 0x0, 0x3, 0x9, 0xff, 0xf0, 0x60,
    0xff, 0xc0, 0xc, 0x7, 0xf8, 0x21, 0x80, 0xff,
    0x6, 0x30, 0x1f, 0xe0, 0x6, 0x0, 0x0, 0x0,
    0xc0, 0x0, 0x0, 0x18, 0x0, 0x0, 0x3, 0x0,
    0x0, 0x0, 0x60, 0x0, 0x0, 0xc, 0x0, 0x0,
    0x1, 0x80, 0x0, 0x0, 0x30, 0x0, 0x0, 0x7,
    0xff, 0xff, 0xff, 0x80,

    /* U+F499 "" */
    0x7f, 0xff, 0xff, 0xfc, 0x80, 0x0, 0x0, 0x9,
    0x0, 0x0, 0x0, 0x21, 0x0, 0x0, 0x0, 0x42,
    0x0, 0x3c, 0x1, 0x2, 0x0, 0xfc, 0x2, 0x6,
    0x1, 0xfc, 0x8, 0x4, 0x7, 0xf8, 0x20, 0x4,
    0xf, 0xf0, 0x40, 0x8, 0xf, 0xc1, 0x0, 0x8,
    0xf, 0x82, 0x0, 0x10, 0x1c, 0x8, 0x0, 0x10,
    0x30, 0x20, 0x0, 0x20, 0x20, 0x40, 0x0, 0x20,
    0x1, 0x0, 0x0, 0x20, 0x82, 0x0, 0x0, 0x41,
    0x8, 0x0, 0x0, 0x40, 0x10, 0x0, 0x0, 0x80,
    0x40, 0x0, 0x0, 0x81, 0x0, 0x0, 0x1, 0x2,
    0x0, 0x0, 0x1, 0x8, 0x0, 0x0, 0x1, 0x10,
    0x0, 0x0, 0x2, 0x40, 0x0, 0x0, 0x3, 0x0,
    0x0, 0x0, 0x2, 0x0, 0x0,

    /* U+F49A "" */
    0xff, 0xff, 0xff, 0xfc, 0x0, 0x0, 0x0, 0x60,
    0x0, 0x0, 0x4, 0x80, 0x0, 0x0, 0x42, 0x0,
    0x50, 0x2, 0x10, 0x6, 0xc0, 0x20, 0x40, 0x77,
    0x1, 0x2, 0x3, 0xb8, 0x10, 0x8, 0x1f, 0xc0,
    0x80, 0x40, 0x7c, 0x8, 0x1, 0x1, 0xc0, 0x80,
    0x4, 0xe, 0x4, 0x0, 0x20, 0x70, 0x40, 0x0,
    0x83, 0x82, 0x0, 0x4, 0x1c, 0x20, 0x0, 0x10,
    0xe1, 0x0, 0x0, 0x87, 0x10, 0x0, 0x2, 0x1,
    0x0, 0x0, 0x10, 0x8, 0x0, 0x0, 0x40, 0x80,
    0x0, 0x1, 0x4, 0x0, 0x0, 0x8, 0x40, 0x0,
    0x0, 0x22, 0x0, 0x0, 0x1, 0x20, 0x0, 0x0,
    0x6, 0x0, 0x0, 0x0, 0x30, 0x0, 0x0,

    /* U+F49B "" */
    0xff, 0xff, 0xff, 0xf0, 0x0, 0x0, 0x6, 0x0,
    0x0, 0x0, 0xc0, 0x0, 0x0, 0x18, 0x0, 0x0,
    0x3, 0x0, 0x0, 0x0, 0x60, 0x0, 0x0, 0xc,
    0x0, 0x0, 0x1, 0x80, 0x80, 0x20, 0x30, 0x8,
    0x8, 0x6, 0x0, 0x82, 0x0, 0xc0, 0x8, 0x80,
    0x18, 0x0, 0xa0, 0x3, 0x0, 0x8, 0x0, 0x60,
    0x2, 0x80, 0xc, 0x0, 0x88, 0x1, 0x80, 0x20,
    0x80, 0x30, 0x8, 0x8, 0x6, 0x2, 0x0, 0x80,
    0xc0, 0x0, 0x0, 0x18, 0x0, 0x0, 0x3, 0x0,
    0x0, 0x0, 0x60, 0x0, 0x0, 0xc, 0x0, 0x0,
    0x1, 0x80, 0x0, 0x0, 0x30, 0x0, 0x0, 0x7,
    0xff, 0xff, 0xff, 0x80,

    /* U+F49C "" */
    0xff, 0xff, 0xff, 0xf0, 0x0, 0x0, 0x6, 0x0,
    0x0, 0x0, 0xc0, 0x0, 0x0, 0x18, 0x0, 0x0,
    0x3, 0x0, 0x0, 0x0, 0x60, 0x0, 0x1, 0xc,
    0x0, 0x0, 0x21, 0x80, 0x0, 0x8, 0x30, 0x0,
    0x2, 0x6, 0x0, 0x0, 0x80, 0xc0, 0x0, 0x10,
    0x18, 0x0, 0x4, 0x3, 0x0, 0x1, 0x0, 0x61,
    0x0, 0x40, 0xc, 0x10, 0x8, 0x1, 0x81, 0x2,
    0x0, 0x30, 0x10, 0x80, 0x6, 0x1, 0x20, 0x0,
    0xc0, 0x18, 0x0, 0x18, 0x1, 0x0, 0x3, 0x0,
    0x0, 0x0, 0x60, 0x0, 0x0, 0xc, 0x0, 0x0,
    0x1, 0x80, 0x0, 0x0, 0x30, 0x0, 0x0, 0x7,
    0xff, 0xff, 0xff, 0x80,

    /* U+F49D "" */
    0xff, 0xff, 0xff, 0xf0, 0x0, 0x0, 0x6, 0x0,
    0x0, 0x0, 0xc0, 0x0, 0x0, 0x18, 0x0, 0x0,
    0x3, 0x0, 0x0, 0x0, 0x60, 0x0, 0x0, 0xc,
    0x0, 0x0, 0x1, 0x80, 0x0, 0x0, 0x30, 0x0,
    0x0, 0x6, 0x0, 0x0, 0x0, 0xc0, 0x0, 0x0,
    0x18, 0x0, 0x0, 0x3, 0x0, 0x0, 0x0, 0x60,
    0x0, 0x0, 0xc, 0x0, 0x0, 0x1, 0x80, 0x0,
    0x0, 0x30, 0x0, 0x0, 0x6, 0x0, 0x0, 0x0,
    0xc0, 0x0, 0x0, 0x18, 0x0, 0x0, 0x3, 0x0,
    0x0, 0x0, 0x60, 0x0, 0x0, 0xc, 0x0, 0x0,
    0x1, 0x80, 0x0, 0x0, 0x30, 0x0, 0x0, 0x7,
    0xff, 0xff, 0xff, 0x80,

    /* U+F4C5 "" */
    0x0, 0x2, 0x0, 0x0, 0x0, 0x70, 0x0, 0x0,
    0xf, 0x80, 0x0, 0x1, 0xfc, 0x0, 0x0, 0x3d,
    0xe0, 0x0, 0x7, 0x8f, 0x0, 0x0, 0xf0, 0x78,
    0x0, 0x1e, 0x3, 0xc0, 0x3, 0xc0, 0x1c, 0x0,
    0x78, 0x1, 0xe0, 0xf, 0x0, 0xf, 0x1, 0xe0,
    0x0, 0x78, 0x3c, 0xff, 0x43, 0xc7, 0x8f, 0xfe,
    0x1e, 0xf0, 0xff, 0xc0, 0xff, 0xf, 0xfb, 0xf,
    0x78, 0xff, 0x31, 0xe3, 0xe0, 0x0, 0x3c, 0x1f,
    0x0, 0x7, 0x80, 0x78, 0x1, 0xf0, 0x3, 0xc0,
    0x3e, 0x0, 0x1e, 0x7, 0xc0, 0x0, 0xf8, 0xf0,
    0x0, 0x7, 0xde, 0x0, 0x0, 0x3f, 0xc0, 0x0,
    0x1, 0xf8, 0x0, 0x0, 0x7, 0x0, 0x0, 0x0,
    0x20, 0x0,

    /* U+F4C6 "" */
    0x0, 0x3, 0x0, 0x0, 0x0, 0xc, 0x0, 0x0,
    0x0, 0x78, 0x0, 0x0, 0x1, 0xe0, 0x0, 0x0,
    0xf, 0xc0, 0x0, 0x0, 0x3f, 0x0, 0x0, 0x1,
    0xce, 0x0, 0x0, 0xf, 0x3c, 0x0, 0x0, 0x38,
    0x70, 0x0, 0x1, 0xe1, 0xe0, 0x0, 0x7, 0x3,
    0x80, 0x0, 0x38, 0xcf, 0x0, 0x1, 0xef, 0xdc,
    0x0, 0x7, 0x31, 0x38, 0x0, 0x3c, 0x4, 0xf0,
    0x0, 0xe0, 0x71, 0xc0, 0x7, 0x83, 0x87, 0x80,
    0x1c, 0xc, 0xe, 0x0, 0xe0, 0x0, 0x3c, 0x7,
    0x80, 0xc0, 0x70, 0x1c, 0x3, 0x0, 0xe0, 0xf0,
    0x0, 0x3, 0xc3, 0xff, 0xff, 0xff, 0x1f, 0xff,
    0xff, 0xfe, 0x7f, 0xff, 0xff, 0xf8,

    /* U+F4C7 "" */
    0xff, 0xff, 0xff, 0xfd, 0xff, 0xff, 0xff, 0xe7,
    0xff, 0xff, 0xff, 0x8f, 0xff, 0xff, 0xfc, 0x1c,
    0x0, 0x0, 0xe0, 0x70, 0x8, 0x3, 0x80, 0xe0,
    0x68, 0x1c, 0x3, 0x81, 0xe0, 0x70, 0x7, 0x7,
    0x83, 0x80, 0x1c, 0xc, 0x1c, 0x0, 0x38, 0x30,
    0x70, 0x0, 0x70, 0xc3, 0x80, 0x1, 0xc3, 0xe,
    0x0, 0x3, 0x8c, 0x70, 0x0, 0xe, 0x31, 0xc0,
    0x0, 0x1c, 0xce, 0x0, 0x0, 0x70, 0x70, 0x0,
    0x0, 0xe1, 0xc0, 0x0, 0x1, 0xce, 0x0, 0x0,
    0x7, 0x38, 0x0, 0x0, 0xf, 0xc0, 0x0, 0x0,
    0x3f, 0x0, 0x0, 0x0, 0x78, 0x0, 0x0, 0x0,
    0xc0, 0x0, 0x0, 0x3, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0,

    /* U+F4C8 "" */
    0x0, 0x7f, 0x80, 0x0, 0x3f, 0xfc, 0x0, 0x1f,
    0x3, 0xe0, 0x7, 0x80, 0x1e, 0x1, 0xc0, 0x0,
    0xe0, 0x73, 0x0, 0xce, 0xe, 0xf0, 0x3d, 0xc3,
    0xbf, 0xf, 0xdc, 0x63, 0xf3, 0xf1, 0x9c, 0x3e,
    0x7c, 0x3b, 0x83, 0xff, 0x7, 0x70, 0x3f, 0xc0,
    0xee, 0x3, 0xf0, 0x1d, 0xc0, 0x7e, 0x3, 0xb8,
    0x1f, 0xe0, 0x77, 0x7, 0xfe, 0xe, 0xe1, 0xff,
    0xe1, 0xcc, 0x7e, 0x7e, 0x31, 0xdf, 0x87, 0xee,
    0x1d, 0xe0, 0x7b, 0x83, 0x98, 0x6, 0x70, 0x38,
    0x0, 0x1c, 0x3, 0xc0, 0xf, 0x0, 0x3e, 0x7,
    0xc0, 0x1, 0xff, 0xe0, 0x0, 0xf, 0xf0, 0x0,

    /* U+F4C9 "" */
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x80,
    0x0, 0x3, 0xf0, 0x0, 0x0, 0x7e, 0x0, 0x0,
    0xf, 0xc0, 0x0, 0x1, 0xf8, 0x0, 0x6, 0x3f,
    0x0, 0x1, 0xe7, 0xe0, 0x0, 0x7c, 0xfc, 0x0,
    0x1f, 0x1f, 0x80, 0x7, 0xc3, 0xf0, 0x1, 0xf0,
    0x7e, 0x0, 0x7c, 0xf, 0xc6, 0x1f, 0x1, 0xf9,
    0xe7, 0xc0, 0x3f, 0x3f, 0xf0, 0x7, 0xe7, 0xfc,
    0x0, 0xfc, 0x7f, 0x0, 0x1f, 0x87, 0xc0, 0x3,
    0xf0, 0x70, 0x0, 0x7e, 0x0, 0x0, 0xf, 0xc0,
    0x0, 0x1, 0xf8, 0x0, 0x0, 0x3f, 0x0, 0x0,
    0x7, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc,

    /* U+F4CA "" */
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x80,
    0x0, 0x3, 0xf0, 0x0, 0x0, 0x7e, 0x0, 0x0,
    0xf, 0xc0, 0x0, 0x1, 0xf8, 0x0, 0x0, 0x3f,
    0x0, 0x0, 0x7, 0xe0, 0x0, 0x0, 0xfc, 0x0,
    0x0, 0x1f, 0x80, 0x0, 0x3, 0xf0, 0x0, 0x0,
    0x7e, 0x0, 0x0, 0xf, 0xc0, 0x0, 0x1, 0xf8,
    0x0, 0x0, 0x3f, 0x0, 0x0, 0x7, 0xe0, 0x0,
    0x0, 0xfc, 0x0, 0x0, 0x1f, 0x80, 0x0, 0x3,
    0xf0, 0x0, 0x0, 0x7e, 0x0, 0x0, 0xf, 0xc0,
    0x0, 0x1, 0xf8, 0x0, 0x0, 0x3f, 0x0, 0x0,
    0x7, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 188, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1, .adv_w = 205, .box_w = 9, .box_h = 2, .ofs_x = 2, .ofs_y = 10},
    {.bitmap_index = 4, .adv_w = 112, .box_w = 3, .box_h = 3, .ofs_x = 2, .ofs_y = 3},
    {.bitmap_index = 6, .adv_w = 288, .box_w = 15, .box_h = 22, .ofs_x = 2, .ofs_y = 3},
    {.bitmap_index = 48, .adv_w = 314, .box_w = 7, .box_h = 22, .ofs_x = 4, .ofs_y = 3},
    {.bitmap_index = 68, .adv_w = 291, .box_w = 15, .box_h = 22, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 110, .adv_w = 278, .box_w = 14, .box_h = 22, .ofs_x = 2, .ofs_y = 3},
    {.bitmap_index = 149, .adv_w = 295, .box_w = 16, .box_h = 22, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 193, .adv_w = 302, .box_w = 14, .box_h = 22, .ofs_x = 2, .ofs_y = 3},
    {.bitmap_index = 232, .adv_w = 292, .box_w = 15, .box_h = 22, .ofs_x = 2, .ofs_y = 3},
    {.bitmap_index = 274, .adv_w = 288, .box_w = 14, .box_h = 22, .ofs_x = 2, .ofs_y = 3},
    {.bitmap_index = 313, .adv_w = 288, .box_w = 15, .box_h = 22, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 355, .adv_w = 286, .box_w = 15, .box_h = 22, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 397, .adv_w = 274, .box_w = 14, .box_h = 16, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 425, .adv_w = 249, .box_w = 12, .box_h = 16, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 449, .adv_w = 274, .box_w = 14, .box_h = 23, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 490, .adv_w = 158, .box_w = 10, .box_h = 23, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 519, .adv_w = 257, .box_w = 16, .box_h = 16, .ofs_x = 0, .ofs_y = 3},
    {.bitmap_index = 551, .adv_w = 420, .box_w = 24, .box_h = 19, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 608, .adv_w = 420, .box_w = 24, .box_h = 19, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 665, .adv_w = 300, .box_w = 19, .box_h = 23, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 720, .adv_w = 300, .box_w = 19, .box_h = 23, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 775, .adv_w = 240, .box_w = 13, .box_h = 19, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 806, .adv_w = 240, .box_w = 13, .box_h = 19, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 837, .adv_w = 300, .box_w = 19, .box_h = 12, .ofs_x = 0, .ofs_y = 5},
    {.bitmap_index = 866, .adv_w = 300, .box_w = 19, .box_h = 12, .ofs_x = 0, .ofs_y = 5},
    {.bitmap_index = 895, .adv_w = 469, .box_w = 27, .box_h = 27, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 987, .adv_w = 488, .box_w = 31, .box_h = 26, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 1088, .adv_w = 487, .box_w = 29, .box_h = 26, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 1183, .adv_w = 469, .box_w = 27, .box_h = 27, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1275, .adv_w = 469, .box_w = 27, .box_h = 27, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1367, .adv_w = 469, .box_w = 27, .box_h = 27, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1459, .adv_w = 480, .box_w = 28, .box_h = 28, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1557, .adv_w = 480, .box_w = 30, .box_h = 25, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1651, .adv_w = 480, .box_w = 30, .box_h = 26, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 1749, .adv_w = 480, .box_w = 27, .box_h = 26, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 1837, .adv_w = 480, .box_w = 27, .box_h = 26, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 1925, .adv_w = 480, .box_w = 27, .box_h = 26, .ofs_x = 2, .ofs_y = 0}
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
const lv_font_t font_Symbols_30 = {
#else
lv_font_t font_Symbols_30 = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 29,          /*The maximum line height required by the font*/
    .base_line = 2,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = -11,
    .underline_thickness = 1,
#endif
    .dsc = &font_dsc           /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
};



#endif /*#if FONT_SYMBOLS_30*/

