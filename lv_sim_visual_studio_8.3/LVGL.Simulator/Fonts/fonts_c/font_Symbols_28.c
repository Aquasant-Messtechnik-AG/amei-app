/*******************************************************************************
 * Size: 28 px
 * Bpp: 1
 * Opts: 
 ******************************************************************************/

#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "lvgl.h"
#endif

#ifndef FONT_SYMBOLS_28
#define FONT_SYMBOLS_28 1
#endif

#if FONT_SYMBOLS_28

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " */
    0x0,

    /* U+002D "-" */
    0xff, 0xff,

    /* U+002E "." */
    0xff, 0x80,

    /* U+0030 "0" */
    0xf, 0xc0, 0x7f, 0x83, 0x87, 0x1c, 0xe, 0x60,
    0x19, 0x80, 0x6c, 0x0, 0xf0, 0x3, 0xc0, 0xf,
    0x0, 0x3c, 0x0, 0xf0, 0x3, 0xc0, 0xf, 0x0,
    0x3c, 0x0, 0xd8, 0x6, 0x60, 0x19, 0xc0, 0xe3,
    0x87, 0x7, 0xf8, 0xf, 0xc0,

    /* U+0031 "1" */
    0xc, 0x77, 0xfb, 0xcc, 0x30, 0xc3, 0xc, 0x30,
    0xc3, 0xc, 0x30, 0xc3, 0xc, 0x30, 0xc3, 0xc,

    /* U+0032 "2" */
    0x1f, 0x83, 0xfe, 0x3c, 0x39, 0x80, 0x60, 0x3,
    0x0, 0x18, 0x0, 0xc0, 0x6, 0x0, 0x60, 0x7,
    0x0, 0x30, 0x3, 0x80, 0x38, 0x3, 0x80, 0x38,
    0x3, 0x80, 0x38, 0x3, 0x80, 0x1c, 0x1, 0xff,
    0xff, 0xff, 0x80,

    /* U+0033 "3" */
    0xf, 0xc0, 0xff, 0xc7, 0x87, 0x18, 0x6, 0x0,
    0x18, 0x0, 0x60, 0x1, 0x80, 0xe, 0x0, 0x70,
    0x3f, 0x80, 0xff, 0x0, 0xe, 0x0, 0x1c, 0x0,
    0x30, 0x0, 0xc0, 0x3, 0x0, 0xd, 0x80, 0x7f,
    0x83, 0x8f, 0xfc, 0xf, 0xc0,

    /* U+0034 "4" */
    0x0, 0x60, 0x3, 0x80, 0xe, 0x0, 0x78, 0x1,
    0xe0, 0xd, 0x80, 0x76, 0x1, 0x98, 0xc, 0x60,
    0x71, 0x81, 0x86, 0xe, 0x18, 0x30, 0x61, 0x81,
    0x8e, 0x6, 0x3f, 0xff, 0xff, 0xfc, 0x1, 0x80,
    0x6, 0x0, 0x18, 0x0, 0x60,

    /* U+0035 "5" */
    0x7f, 0xf9, 0xff, 0xe6, 0x0, 0x18, 0x0, 0x60,
    0x1, 0x80, 0x6, 0x0, 0x18, 0x0, 0x67, 0xc1,
    0xff, 0xc7, 0x83, 0x98, 0x6, 0x0, 0xc, 0x0,
    0x30, 0x0, 0xc0, 0x3, 0x0, 0xd, 0x0, 0x6f,
    0x83, 0x8f, 0xfc, 0xf, 0xc0,

    /* U+0036 "6" */
    0x7, 0xe0, 0x7f, 0xe3, 0xc3, 0xcc, 0x3, 0x60,
    0x1, 0x80, 0xe, 0x0, 0x30, 0x0, 0xc7, 0xc3,
    0x7f, 0xcd, 0x83, 0xbc, 0x6, 0xe0, 0xf, 0x80,
    0x3e, 0x0, 0xd8, 0x3, 0x60, 0xd, 0xc0, 0x63,
    0x83, 0x87, 0xfc, 0x7, 0xc0,

    /* U+0037 "7" */
    0xff, 0xff, 0xff, 0xc0, 0xe, 0x0, 0x60, 0x7,
    0x0, 0x30, 0x3, 0x80, 0x18, 0x1, 0xc0, 0xc,
    0x0, 0xe0, 0x6, 0x0, 0x70, 0x3, 0x0, 0x38,
    0x1, 0x80, 0x1c, 0x0, 0xc0, 0x6, 0x0, 0x70,
    0x3, 0x0, 0x0,

    /* U+0038 "8" */
    0x7, 0xc0, 0x7f, 0xc3, 0x83, 0x9c, 0x7, 0x60,
    0xd, 0x80, 0x36, 0x0, 0xd8, 0x7, 0x30, 0x38,
    0x7b, 0xc0, 0xfe, 0xe, 0x3e, 0x60, 0x1b, 0x0,
    0x3c, 0x0, 0xf0, 0x3, 0xc0, 0xf, 0x80, 0x77,
    0x3, 0x8f, 0xfc, 0xf, 0xc0,

    /* U+0039 "9" */
    0xf, 0x80, 0xff, 0x87, 0x7, 0x18, 0xe, 0xc0,
    0x1b, 0x0, 0x6c, 0x1, 0xf0, 0x7, 0xc0, 0x1d,
    0x80, 0xf7, 0x6, 0xcf, 0xfb, 0xf, 0x8c, 0x0,
    0x30, 0x1, 0xc0, 0x6, 0x0, 0x1b, 0x0, 0xcf,
    0xf, 0x1f, 0xf8, 0x1f, 0x80,

    /* U+0061 "a" */
    0xf, 0x99, 0xfe, 0xdc, 0x1e, 0xc0, 0x7e, 0x1,
    0xe0, 0xf, 0x0, 0x78, 0x3, 0xc0, 0x1e, 0x0,
    0xf8, 0xe, 0xc0, 0x77, 0x7, 0x9f, 0xec, 0x3e,
    0x60,

    /* U+0063 "c" */
    0xf, 0x87, 0xfd, 0xc1, 0xb0, 0x1e, 0x1, 0x80,
    0x30, 0x6, 0x0, 0xc0, 0x18, 0x3, 0x80, 0x30,
    0x7, 0x6, 0x7f, 0xc3, 0xe0,

    /* U+0064 "d" */
    0x0, 0x18, 0x0, 0xc0, 0x6, 0x0, 0x30, 0x1,
    0x80, 0xc, 0x3e, 0x67, 0xfb, 0x70, 0x7b, 0x1,
    0xf8, 0xf, 0x80, 0x3c, 0x1, 0xe0, 0xf, 0x0,
    0x78, 0x3, 0xe0, 0x3b, 0x1, 0xdc, 0x1e, 0x7f,
    0xb0, 0xf9, 0x80,

    /* U+0066 "f" */
    0x7, 0x87, 0xc7, 0x3, 0x1, 0x80, 0xc3, 0xfd,
    0xfe, 0x18, 0xc, 0x6, 0x3, 0x1, 0x80, 0xc0,
    0x60, 0x30, 0x18, 0xc, 0x6, 0x3, 0x1, 0x80,

    /* U+0078 "x" */
    0x70, 0x1c, 0x70, 0x70, 0x60, 0xc0, 0xe3, 0x80,
    0xee, 0x0, 0xd8, 0x0, 0xe0, 0x1, 0xc0, 0x7,
    0xc0, 0x1d, 0xc0, 0x31, 0x80, 0xe3, 0x83, 0x83,
    0x8e, 0x3, 0x98, 0x3, 0x0,

    /* U+F100 "" */
    0x0, 0xc0, 0x18, 0x7, 0x81, 0xf0, 0x3f, 0xf,
    0xc1, 0xf8, 0x7f, 0xf, 0xc3, 0xf8, 0x7e, 0x1f,
    0xc3, 0xf0, 0xfe, 0x1f, 0x87, 0xf0, 0xfc, 0x1f,
    0x81, 0xf8, 0x7f, 0x3, 0xf0, 0xfe, 0x7, 0xe1,
    0xfc, 0xf, 0xc3, 0xf8, 0x1f, 0x87, 0xf0, 0x3f,
    0x7, 0xc0, 0x78, 0xf, 0x0, 0xc0, 0x18,

    /* U+F101 "" */
    0x30, 0xc, 0x1, 0xe0, 0x78, 0xf, 0xc1, 0xf8,
    0x1f, 0x87, 0xf0, 0x3f, 0xf, 0xe0, 0x7e, 0x1f,
    0xc0, 0xfc, 0x3f, 0x81, 0xf8, 0x7f, 0x3, 0xf0,
    0x7c, 0x1f, 0x87, 0xf0, 0xfc, 0x3f, 0x87, 0xe1,
    0xfc, 0x3f, 0xf, 0xe1, 0xf8, 0x7f, 0xf, 0xc1,
    0xf8, 0x1e, 0x7, 0x80, 0x30, 0xc, 0x0,

    /* U+F102 "" */
    0x0, 0xc0, 0x0, 0xfc, 0x0, 0x7f, 0x80, 0x3f,
    0xf0, 0x1f, 0xfe, 0xf, 0xff, 0xc7, 0xf3, 0xfb,
    0xf8, 0x7f, 0xfc, 0xf, 0xde, 0x1, 0xe3, 0xc,
    0x30, 0x7, 0x80, 0x3, 0xf0, 0x1, 0xfe, 0x0,
    0xff, 0xc0, 0x7f, 0xf8, 0x3f, 0x3f, 0x1f, 0x87,
    0xef, 0xc0, 0xff, 0xe0, 0x1f, 0x70, 0x3, 0x80,

    /* U+F103 "" */
    0x70, 0x3, 0xbe, 0x1, 0xff, 0xc0, 0xfd, 0xf8,
    0x7e, 0x3f, 0x3f, 0x7, 0xff, 0x80, 0xff, 0xc0,
    0x1f, 0xe0, 0x3, 0xf0, 0x0, 0x78, 0x3, 0xc,
    0x31, 0xe0, 0x1e, 0xfc, 0xf, 0xff, 0x87, 0xf7,
    0xf3, 0xf8, 0xff, 0xfc, 0x1f, 0xfe, 0x3, 0xff,
    0x0, 0x7f, 0x80, 0xf, 0xc0, 0x0, 0xc0, 0x0,

    /* U+F104 "" */
    0x0, 0xc0, 0x1e, 0x3, 0xf0, 0x7e, 0xf, 0xc1,
    0xf8, 0x3f, 0x7, 0xe0, 0xfc, 0x7, 0xe0, 0x3f,
    0x1, 0xf8, 0xf, 0xc0, 0x7e, 0x3, 0xf0, 0x1e,
    0x0, 0xc0,

    /* U+F105 "" */
    0x30, 0x7, 0x80, 0xfc, 0x7, 0xe0, 0x3f, 0x1,
    0xf8, 0xf, 0xc0, 0x7e, 0x3, 0xf0, 0x7e, 0xf,
    0xc1, 0xf8, 0x3f, 0x7, 0xe0, 0xfc, 0x7, 0x80,
    0x30, 0x0,

    /* U+F106 "" */
    0x0, 0xc0, 0x0, 0x78, 0x0, 0x3f, 0x0, 0x1f,
    0xe0, 0xf, 0xfc, 0x7, 0xff, 0x83, 0xf3, 0xf1,
    0xf8, 0x7e, 0xfc, 0xf, 0xfe, 0x1, 0xf7, 0x0,
    0x38,

    /* U+F107 "" */
    0x70, 0x3, 0xbe, 0x1, 0xff, 0xc0, 0xfd, 0xf8,
    0x7e, 0x3f, 0x3f, 0x7, 0xff, 0x80, 0xff, 0xc0,
    0x1f, 0xe0, 0x3, 0xf0, 0x0, 0x78, 0x0, 0xc,
    0x0,

    /* U+F498 "" */
    0xff, 0xff, 0xff, 0xc0, 0x0, 0x0, 0x60, 0x0,
    0x0, 0x30, 0x0, 0x0, 0x18, 0x0, 0x0, 0xc,
    0x7f, 0xe1, 0x86, 0x3f, 0xf1, 0xc3, 0xf, 0xfb,
    0xc1, 0x87, 0xff, 0xc0, 0xc3, 0xff, 0xc0, 0x61,
    0xff, 0xc0, 0x30, 0xff, 0xc0, 0x18, 0x0, 0x0,
    0xc, 0x0, 0x0, 0x6, 0x0, 0x0, 0x3, 0x0,
    0x0, 0x1, 0x80, 0x7, 0xf0, 0xc0, 0x7, 0xfe,
    0x60, 0x7, 0xfe, 0x30, 0x7, 0xff, 0x18, 0x3,
    0xfc, 0xc, 0x0, 0x0, 0x6, 0x0, 0x0, 0x3,
    0x0, 0x0, 0x1, 0xff, 0xff, 0xff, 0x80,

    /* U+F499 "" */
    0xff, 0xff, 0xff, 0xc0, 0x0, 0x0, 0x60, 0x0,
    0x0, 0x30, 0x3, 0xc0, 0x18, 0x7, 0xf8, 0xc,
    0x3, 0xc, 0x6, 0x3, 0x3, 0x3, 0x1, 0x81,
    0x81, 0x80, 0xc0, 0xc0, 0xc0, 0x40, 0x60, 0x60,
    0x0, 0x70, 0x30, 0x0, 0x70, 0x18, 0x0, 0x70,
    0xc, 0x0, 0x60, 0x6, 0x0, 0x30, 0x3, 0x0,
    0x30, 0x1, 0x80, 0x18, 0x0, 0xc0, 0x0, 0x0,
    0x60, 0x0, 0x0, 0x30, 0x3, 0x0, 0x18, 0x1,
    0x80, 0xc, 0x0, 0xc0, 0x6, 0x0, 0x0, 0x3,
    0x0, 0x0, 0x1, 0xff, 0xff, 0xff, 0x80,

    /* U+F49A "" */
    0xff, 0xff, 0xff, 0xc0, 0x0, 0x0, 0x60, 0x0,
    0x0, 0x30, 0x0, 0x0, 0x18, 0x6, 0x30, 0xc,
    0x7, 0x1c, 0x6, 0x7, 0x8f, 0x3, 0x3, 0xc7,
    0x81, 0x81, 0xff, 0xc0, 0xc0, 0xff, 0xe0, 0x60,
    0x3f, 0xe0, 0x30, 0xf, 0xe0, 0x18, 0x3, 0xe0,
    0xc, 0x1, 0xf0, 0x6, 0x0, 0xf8, 0x3, 0x0,
    0x7c, 0x1, 0x80, 0x3e, 0x0, 0xc0, 0x1f, 0x0,
    0x60, 0xf, 0x80, 0x30, 0x7, 0xc0, 0x18, 0x3,
    0xe0, 0xc, 0x0, 0x0, 0x6, 0x0, 0x0, 0x3,
    0x0, 0x0, 0x1, 0xff, 0xff, 0xff, 0x80,

    /* U+F49B "" */
    0xff, 0xff, 0xff, 0xc0, 0x0, 0x0, 0x60, 0x0,
    0x0, 0x30, 0x0, 0x0, 0x18, 0x0, 0x0, 0xc,
    0x70, 0x1, 0x86, 0x1c, 0x1, 0xc3, 0x7, 0x1,
    0xc1, 0x81, 0xc1, 0xc0, 0xc0, 0x71, 0xc0, 0x60,
    0x1d, 0xc0, 0x30, 0x7, 0xc0, 0x18, 0x1, 0xc0,
    0xc, 0x1, 0xf0, 0x6, 0x1, 0xdc, 0x3, 0x1,
    0xc7, 0x1, 0x81, 0xc1, 0xc0, 0xc1, 0xc0, 0x70,
    0x61, 0xc0, 0x1c, 0x30, 0xc0, 0x6, 0x18, 0x40,
    0x0, 0xc, 0x0, 0x0, 0x6, 0x0, 0x0, 0x3,
    0x0, 0x0, 0x1, 0xff, 0xff, 0xff, 0x80,

    /* U+F49C "" */
    0xff, 0xff, 0xff, 0xc0, 0x0, 0x0, 0x60, 0x0,
    0x0, 0x30, 0x0, 0x0, 0x18, 0x0, 0x0, 0xc,
    0x0, 0x0, 0x46, 0x0, 0x0, 0x63, 0x0, 0x0,
    0x61, 0x80, 0x0, 0x60, 0xc0, 0x0, 0x30, 0x60,
    0x0, 0x30, 0x30, 0x0, 0x30, 0x18, 0x80, 0x30,
    0xc, 0x60, 0x18, 0x6, 0x18, 0x18, 0x3, 0x6,
    0x18, 0x1, 0x81, 0x98, 0x0, 0xc0, 0x78, 0x0,
    0x60, 0x1c, 0x0, 0x30, 0x4, 0x0, 0x18, 0x0,
    0x0, 0xc, 0x0, 0x0, 0x6, 0x0, 0x0, 0x3,
    0x0, 0x0, 0x1, 0xff, 0xff, 0xff, 0x80,

    /* U+F49D "" */
    0xff, 0xff, 0xff, 0xc0, 0x0, 0x0, 0x60, 0x0,
    0x0, 0x30, 0x0, 0x0, 0x18, 0x0, 0x0, 0xc,
    0x0, 0x0, 0x6, 0x0, 0x0, 0x3, 0x0, 0x0,
    0x1, 0x80, 0x0, 0x0, 0xc0, 0x0, 0x0, 0x60,
    0x0, 0x0, 0x30, 0x0, 0x0, 0x18, 0x0, 0x0,
    0xc, 0x0, 0x0, 0x6, 0x0, 0x0, 0x3, 0x0,
    0x0, 0x1, 0x80, 0x0, 0x0, 0xc0, 0x0, 0x0,
    0x60, 0x0, 0x0, 0x30, 0x0, 0x0, 0x18, 0x0,
    0x0, 0xc, 0x0, 0x0, 0x6, 0x0, 0x0, 0x3,
    0x0, 0x0, 0x1, 0xff, 0xff, 0xff, 0x80,

    /* U+F4C5 "" */
    0x0, 0x6, 0x0, 0x0, 0x1, 0xc0, 0x0, 0x0,
    0x7c, 0x0, 0x0, 0x1f, 0xc0, 0x0, 0x7, 0x1c,
    0x0, 0x1, 0xc1, 0xc0, 0x0, 0x78, 0x1c, 0x0,
    0x1c, 0x3, 0xc0, 0x7, 0x0, 0x3c, 0x1, 0xc0,
    0x3, 0xc0, 0x70, 0x0, 0x3c, 0x1c, 0x7f, 0x43,
    0xc7, 0xf, 0xf8, 0x3d, 0xc1, 0xfe, 0x3, 0xde,
    0x3f, 0x98, 0xf1, 0xe0, 0x0, 0x38, 0x1e, 0x0,
    0xe, 0x1, 0xe0, 0x7, 0x80, 0x1f, 0x1, 0xe0,
    0x0, 0xf0, 0x78, 0x0, 0xf, 0x1e, 0x0, 0x0,
    0xf7, 0x80, 0x0, 0xf, 0xe0, 0x0, 0x0, 0xf8,
    0x0, 0x0, 0x6, 0x0, 0x0,

    /* U+F4C6 "" */
    0x0, 0x0, 0x0, 0x0, 0x0, 0x60, 0x0, 0x0,
    0x6, 0x0, 0x0, 0x0, 0xf0, 0x0, 0x0, 0x1f,
    0x0, 0x0, 0x1, 0xf8, 0x0, 0x0, 0x3f, 0xc0,
    0x0, 0x3, 0x9c, 0x0, 0x0, 0x79, 0xe0, 0x0,
    0x7, 0xe, 0x0, 0x0, 0xf0, 0xf0, 0x0, 0x1e,
    0x7, 0x0, 0x1, 0xef, 0x78, 0x0, 0x3d, 0x9b,
    0xc0, 0x3, 0x90, 0x9c, 0x0, 0x78, 0x19, 0xe0,
    0x7, 0x3, 0xe, 0x0, 0xf0, 0x60, 0xf0, 0x1e,
    0x0, 0x7, 0x81, 0xe0, 0x60, 0x78, 0x3c, 0x0,
    0x3, 0xc3, 0x80, 0x0, 0x1c, 0x7f, 0xff, 0xff,
    0xe7, 0xff, 0xff, 0xfe,

    /* U+F4C7 "" */
    0xff, 0xff, 0xff, 0xf7, 0xff, 0xff, 0xfe, 0x7f,
    0xff, 0xff, 0xe3, 0xff, 0xff, 0xfc, 0x38, 0x0,
    0x1, 0xc1, 0xc0, 0x40, 0x38, 0xc, 0xd, 0x3,
    0x0, 0xe0, 0xf0, 0x70, 0x6, 0xf, 0xe, 0x0,
    0x70, 0x60, 0xe0, 0x3, 0x86, 0x1c, 0x0, 0x38,
    0x61, 0x80, 0x1, 0xc6, 0x38, 0x0, 0xc, 0x63,
    0x0, 0x0, 0xe6, 0x70, 0x0, 0x7, 0xe, 0x0,
    0x0, 0x70, 0xe0, 0x0, 0x3, 0x9c, 0x0, 0x0,
    0x19, 0x80, 0x0, 0x1, 0xf8, 0x0, 0x0, 0xf,
    0x0, 0x0, 0x0, 0xf0, 0x0, 0x0, 0x6, 0x0,
    0x0, 0x0, 0x40, 0x0,

    /* U+F4C8 "" */
    0x0, 0x7f, 0x80, 0x0, 0x7f, 0xf8, 0x0, 0x3c,
    0xf, 0x80, 0x3c, 0x0, 0xf0, 0x1e, 0x0, 0xe,
    0x7, 0x60, 0x1b, 0x83, 0xbc, 0xf, 0x70, 0xcf,
    0x87, 0xcc, 0x71, 0xf3, 0xe3, 0x9c, 0x3f, 0xf0,
    0xe6, 0x7, 0xf8, 0x19, 0x80, 0xfc, 0x6, 0x60,
    0x3f, 0x1, 0x98, 0x1f, 0xe0, 0x67, 0xf, 0xfc,
    0x39, 0xc7, 0xcf, 0x8e, 0x33, 0xe1, 0xf3, 0xe,
    0xf0, 0x3d, 0xc1, 0xd8, 0x6, 0xe0, 0x34, 0x1,
    0x30, 0xf, 0x0, 0x3c, 0x0, 0xf0, 0x3c, 0x0,
    0x1f, 0xfe, 0x0, 0x0, 0xfc, 0x0,

    /* U+F4C9 "" */
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0x0,
    0x3, 0xc0, 0x0, 0x3, 0xc0, 0x0, 0x3, 0xc0,
    0x0, 0x63, 0xc0, 0x0, 0xf3, 0xc0, 0x1, 0xfb,
    0xc0, 0x3, 0xe3, 0xc0, 0x7, 0xc3, 0xc0, 0xf,
    0x83, 0xc0, 0x1f, 0x3, 0xc6, 0x3e, 0x3, 0xcf,
    0x7e, 0x3, 0xcf, 0xf8, 0x3, 0xc7, 0xf0, 0x3,
    0xc3, 0xe0, 0x3, 0xc1, 0xc0, 0x3, 0xc0, 0xc0,
    0x3, 0xc0, 0x0, 0x3, 0xc0, 0x0, 0x3, 0xc0,
    0x0, 0x3, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,

    /* U+F4CA "" */
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0x0,
    0x3, 0xc0, 0x0, 0x3, 0xc0, 0x0, 0x3, 0xc0,
    0x0, 0x3, 0xc0, 0x0, 0x3, 0xc0, 0x0, 0x3,
    0xc0, 0x0, 0x3, 0xc0, 0x0, 0x3, 0xc0, 0x0,
    0x3, 0xc0, 0x0, 0x3, 0xc0, 0x0, 0x3, 0xc0,
    0x0, 0x3, 0xc0, 0x0, 0x3, 0xc0, 0x0, 0x3,
    0xc0, 0x0, 0x3, 0xc0, 0x0, 0x3, 0xc0, 0x0,
    0x3, 0xc0, 0x0, 0x3, 0xc0, 0x0, 0x3, 0xc0,
    0x0, 0x3, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 175, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1, .adv_w = 192, .box_w = 8, .box_h = 2, .ofs_x = 2, .ofs_y = 10},
    {.bitmap_index = 3, .adv_w = 104, .box_w = 3, .box_h = 3, .ofs_x = 2, .ofs_y = 3},
    {.bitmap_index = 5, .adv_w = 269, .box_w = 14, .box_h = 21, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 42, .adv_w = 293, .box_w = 6, .box_h = 21, .ofs_x = 4, .ofs_y = 3},
    {.bitmap_index = 58, .adv_w = 271, .box_w = 13, .box_h = 21, .ofs_x = 2, .ofs_y = 3},
    {.bitmap_index = 93, .adv_w = 260, .box_w = 14, .box_h = 21, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 130, .adv_w = 276, .box_w = 14, .box_h = 21, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 167, .adv_w = 282, .box_w = 14, .box_h = 21, .ofs_x = 2, .ofs_y = 3},
    {.bitmap_index = 204, .adv_w = 272, .box_w = 14, .box_h = 21, .ofs_x = 2, .ofs_y = 3},
    {.bitmap_index = 241, .adv_w = 269, .box_w = 13, .box_h = 21, .ofs_x = 2, .ofs_y = 3},
    {.bitmap_index = 276, .adv_w = 269, .box_w = 14, .box_h = 21, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 313, .adv_w = 267, .box_w = 14, .box_h = 21, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 350, .adv_w = 256, .box_w = 13, .box_h = 15, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 375, .adv_w = 233, .box_w = 11, .box_h = 15, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 396, .adv_w = 256, .box_w = 13, .box_h = 21, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 431, .adv_w = 148, .box_w = 9, .box_h = 21, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 455, .adv_w = 240, .box_w = 15, .box_h = 15, .ofs_x = 0, .ofs_y = 3},
    {.bitmap_index = 484, .adv_w = 392, .box_w = 22, .box_h = 17, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 531, .adv_w = 392, .box_w = 22, .box_h = 17, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 578, .adv_w = 280, .box_w = 18, .box_h = 21, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 626, .adv_w = 280, .box_w = 18, .box_h = 21, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 674, .adv_w = 224, .box_w = 12, .box_h = 17, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 700, .adv_w = 224, .box_w = 12, .box_h = 17, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 726, .adv_w = 280, .box_w = 18, .box_h = 11, .ofs_x = 0, .ofs_y = 5},
    {.bitmap_index = 751, .adv_w = 280, .box_w = 18, .box_h = 11, .ofs_x = 0, .ofs_y = 5},
    {.bitmap_index = 776, .adv_w = 438, .box_w = 25, .box_h = 25, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 855, .adv_w = 455, .box_w = 25, .box_h = 25, .ofs_x = 2, .ofs_y = -2},
    {.bitmap_index = 934, .adv_w = 454, .box_w = 25, .box_h = 25, .ofs_x = 2, .ofs_y = -2},
    {.bitmap_index = 1013, .adv_w = 438, .box_w = 25, .box_h = 25, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1092, .adv_w = 438, .box_w = 25, .box_h = 25, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1171, .adv_w = 438, .box_w = 25, .box_h = 25, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1250, .adv_w = 448, .box_w = 27, .box_h = 25, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1335, .adv_w = 448, .box_w = 28, .box_h = 24, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 1419, .adv_w = 448, .box_w = 28, .box_h = 24, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 1503, .adv_w = 448, .box_w = 26, .box_h = 24, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1581, .adv_w = 448, .box_w = 24, .box_h = 24, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 1653, .adv_w = 448, .box_w = 24, .box_h = 24, .ofs_x = 2, .ofs_y = 0}
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
const lv_font_t font_Symbols_28 = {
#else
lv_font_t font_Symbols_28 = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 27,          /*The maximum line height required by the font*/
    .base_line = 2,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = -10,
    .underline_thickness = 1,
#endif
    .dsc = &font_dsc           /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
};



#endif /*#if FONT_SYMBOLS_28*/

