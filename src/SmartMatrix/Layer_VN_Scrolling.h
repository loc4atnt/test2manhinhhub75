/*
 * SmartMatrix Library - Scrolling Layer Class
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

#ifndef _LAYER_VN_SCROLLING_H_
#define _LAYER_VN_SCROLLING_H_

#include "Layer.h"
#include "MatrixCommon.h"

// scroll text
const int textVNLayerMaxStringLength = 3000;

// #define SM_SCROLLING_OPTIONS_NONE     0
#define SM_VN_SCROLLING_OPTIONS_NONE     0

// font
#include "FontMaker/VNFont/VNFont.h"

// define cua tao
#define MAX_BOT_OFFFSET 2

template <typename RGB, unsigned int optionFlags>
class SMLayerVNScrolling : public SM_Layer {
    public:
        SMLayerVNScrolling(uint8_t * bitmap, uint16_t width, uint16_t height);
        SMLayerVNScrolling(uint16_t width, uint16_t height);
        void begin(void);
        void frameRefreshCallback();
        void fillRefreshRow(uint16_t hardwareY, rgb48 refreshRow[], int brightnessShifts = 0);
        void fillRefreshRow(uint16_t hardwareY, rgb24 refreshRow[], int brightnessShifts = 0);

        void setRefreshRate(uint8_t newRefreshRate);

        // size of bitmap is 1 bit per pixel for width*height (no need for double buffering)
        uint8_t * scrollingBitmap;

        void stop(void);
        int getStatus(void) const;
        void start(const char inputtext[], int numScrolls);
        void update(const char inputtext[]);
        void setMode(ScrollMode mode);
        void setColor(const RGB & newColor);
        void setSpeed(unsigned char pixels_per_second);
        void setFont(VNFont *newFont);
        void setOffsetFromTop(int offset);
        void setStartOffsetFromLeft(int offset);
        void enableColorCorrection(bool enabled);

        void setOriginalX(int16_t x0);

    private:
        void redrawScrollingText(void);
        void setMinMax(void);

        void updateScrollingText(void);

        template <typename RGB_OUT>
        bool getPixel(uint16_t hardwareX, uint16_t hardwareY, RGB_OUT &xyPixel);
        bool getPixel(uint16_t hardwareX, uint16_t hardwareY);

        RGB textcolor;
        unsigned char currentframe = 0;
        char text[textVNLayerMaxStringLength+1];
        unsigned char pixelsPerSecond = 30;

        int16_t textlen;
        volatile int scrollcounter = 0;
        // const bitmap_font *scrollFont = &apple5x7;
        VNFont *scrollFont = (VNFont *)&VNFontTypeTahoma;

        int fontTopOffset = 1;
        int fontLeftOffset = 1;
        bool majorScrollFontChange = false;

        bool ccEnabled = sizeof(RGB) <= 3 ? true : false;
        // bool ccEnabled = false;
        ScrollMode scrollmode = bounceForward;
        unsigned char framesperscroll = 4;

        // these variables describe the text bitmap: size, location on the screen, and bounds of where it moves
        int16_t textWidth;
        int textMaxHeight;
        int8_t textMaxBaselineOffset = 0;
        int scrollMin, scrollMax;
        int scrollPosition;

        // cua tao
        int16_t originalX = 0;
};

#include "Layer_VN_Scrolling_Impl.h"

#endif

