/*
 * SmartMatrix Library - Methods for accessing bitmap fonts
 *
 * Copyright (c) 2020 Louis Beaudoin (Pixelmatix)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#ifndef MATRIXFONTCOMMON_H_
#define MATRIXFONTCOMMON_H_

#include <stdbool.h>
#include <stdint.h>

#include "FontMaker/VNFont/HumanReadableBitmap.h"

	/// bitmap font structure
typedef struct bitmap_font {
	unsigned char Width;		///< max. character width
	unsigned char Height;		///< character height
	unsigned short Chars;		///< number of characters in font
	const unsigned char *Widths;	///< width of each character
	const unsigned short *Index;	///< encoding to character index
	const unsigned char *Bitmap;	///< bitmap of all characters
} bitmap_font;


extern const bitmap_font apple3x5;
extern const bitmap_font apple5x7;
extern const bitmap_font apple6x10;
extern const bitmap_font apple8x13;
extern const bitmap_font gohufont6x11;
extern const bitmap_font gohufont6x11b;

typedef enum fontChoices {
    font3x5,
    font5x7,
    font6x10,
    font8x13,
    gohufont11,
    gohufont11b
} fontChoices;

bool getBitmapFontPixelAtXY(unsigned char letter, unsigned char x, unsigned char y, const bitmap_font *font);
const bitmap_font *fontLookup(fontChoices font);
uint16_t getBitmapFontRowAtXY(unsigned char letter, unsigned char y, const bitmap_font *font);
bool getBitmapPixelAtXY(uint8_t x, uint8_t y, uint8_t width, uint8_t height, const uint8_t *bitmap);

#endif /* MATRIXFONTCOMMON_H_ */
