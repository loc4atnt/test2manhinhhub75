#ifndef _VNFont_H_
#define _VNFont_H_

#include "../MyFontMaker.h"

class VNFont {
public:
	VNFont(const MyFont_typedef myFontType);
	unsigned int getTextWidth(char *charSet);
	int getMaxHeight(char *charSet);
	int8_t getMaxBaselineOffset(char *charSet);
	unsigned int getCharWidth(char *charSet, unsigned int textPosition);
	unsigned int getCharHeight(char *charSet, unsigned int textPosition);
	unsigned int getCharHeight(char *charSet);
	int16_t getYOffset(char *charSet);
	unsigned int getCharWidth(char *charSet);
	void nextChar(char **txtPtr);
	uint8_t getCharBitmapRowAtY(char *charSet, int y, uint8_t byteIdx);
	char* getTextPointerAtPostion(char *charSet, int textPosition);
	uint16_t getTextLength(char *charSet);
	uint8_t getMidLine();
	char* getFirstVnCharOutOfWidth(char *charSet, uint8_t maxWidth);

	MyFont_typedef fontMap;
private:
	unsigned int getCharWidth(uint16_t utf8AddrOfChar);
	unsigned int getCharHeight(uint16_t utf8AddrOfChar);
	unsigned int getBaselineOffset(uint16_t utf8AddrOfChar);
	int16_t getYOffset(uint16_t utf8AddrOfChar);
};

extern const VNFont VNFontTypeTahoma;

#endif