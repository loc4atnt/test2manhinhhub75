#include "VNFont.h"

#include "../IOT47_UTF8.h"

VNFont::VNFont(const MyFont_typedef myFontType){
	fontMap = myFontType;
}

unsigned int VNFont::getCharWidth(uint16_t utf8AddrOfChar){
	unsigned int str = pgm_read_word(fontMap.f_map + utf8AddrOfChar);
    return pgm_read_byte( str  + fontMap.f_name - 4); //lấy chiều rộng Font
}

unsigned int VNFont::getCharHeight(uint16_t utf8AddrOfChar){
	unsigned int str = pgm_read_word(fontMap.f_map + utf8AddrOfChar);
    return pgm_read_byte( str  + fontMap.f_name - 3); //lấy chiều cao Font 
}

unsigned int VNFont::getTextWidth(char *charSet){
	unsigned int textWidth = 0;
	unsigned char offset=0;
	uint16_t utf8_addr;
	while(*charSet)
	{

		utf8_addr=UTF8_GetAddr((unsigned char *)charSet,&offset);
		textWidth +=getCharWidth(utf8_addr)+1;
		charSet+=offset;
	}
	return textWidth;
}

int VNFont::getMaxHeight(char *charSet){
	unsigned int maxOffsetBaseline = 0;
	unsigned int maxH = 0;
	unsigned int hTemp;
	unsigned int osTemp;
	unsigned char offset=0;
	uint16_t utf8_addr;
	while(*charSet)
	{
		utf8_addr=UTF8_GetAddr((unsigned char *)charSet,&offset);
		hTemp =getCharHeight(utf8_addr);
		osTemp =getBaselineOffset(utf8_addr);
		if (hTemp>maxH) maxH = hTemp;
		if (osTemp>maxOffsetBaseline) maxOffsetBaseline = osTemp;
		charSet+=offset;
	}
	return maxH + maxOffsetBaseline;
}

int8_t VNFont::getMaxBaselineOffset(char *charSet){
	unsigned int maxOffsetBaseline = 0;
	unsigned int osTemp;
	unsigned char offset=0;
	uint16_t utf8_addr;
	while(*charSet)
	{
		utf8_addr=UTF8_GetAddr((unsigned char *)charSet,&offset);
		osTemp =getBaselineOffset(utf8_addr);
		if (osTemp>maxOffsetBaseline) maxOffsetBaseline = osTemp;
		charSet+=offset;
	}
	return maxOffsetBaseline;
}

unsigned int VNFont::getCharWidth(char *charSet, unsigned int textPosition){
	unsigned char offset=0;
	uint16_t utf8_addr;
	uint8_t txtIdx = 0;
	while(*charSet)
	{
		utf8_addr=UTF8_GetAddr((unsigned char *)charSet,&offset);
		if (txtIdx == textPosition) return getCharWidth(utf8_addr);
		charSet+=offset;
		txtIdx++;
	}
	return 0;
}

unsigned int VNFont::getCharHeight(char *charSet, unsigned int textPosition){
	unsigned char offset=0;
	uint16_t utf8_addr;
	uint8_t txtIdx = 0;
	while(*charSet)
	{
		utf8_addr=UTF8_GetAddr((unsigned char *)charSet,&offset);
		if (txtIdx == textPosition) return getCharHeight(utf8_addr);
		charSet+=offset;
		txtIdx++;
	}
	return 0;
}

unsigned int VNFont::getBaselineOffset(uint16_t utf8AddrOfChar){
	unsigned int str = pgm_read_word(fontMap.f_map + utf8AddrOfChar);
	return pgm_read_byte( str  + fontMap.f_name - 1);
}

int16_t VNFont::getYOffset(uint16_t utf8AddrOfChar){
	unsigned int str = pgm_read_word(fontMap.f_map + utf8AddrOfChar);

	int16_t yOffset=pgm_read_byte( str  + fontMap.f_name - 1);
	if (yOffset>0) yOffset+=1;

    int size_w = pgm_read_byte( str  + fontMap.f_name - 4); //lấy chiều rộng Font
    int size_h = pgm_read_byte( str  + fontMap.f_name - 3); //lấy chiều cao Font 
    int mid_line = pgm_read_byte(fontMap.f_name); //lấy mid line - đường cơ bản
    // if(size_h < mid_line) yOffset+=(mid_line-size_h);
    yOffset+=(mid_line-size_h);
    return yOffset;
}

int16_t VNFont::getYOffset(char *charSet){
	unsigned char offset=0;
	return getYOffset(UTF8_GetAddr((unsigned char *)charSet,&offset));
}

unsigned int VNFont::getCharHeight(char *charSet){
	unsigned char offset=0;
	return getCharHeight(UTF8_GetAddr((unsigned char *)charSet,&offset));
}

unsigned int VNFont::getCharWidth(char *charSet){
	unsigned char offset=0;
	return getCharWidth(UTF8_GetAddr((unsigned char *)charSet,&offset));
}

char* VNFont::getTextPointerAtPostion(char *charSet, int textPosition){
	unsigned char offset=0;
	uint8_t txtIdx = 0;
	while(*charSet)
	{
		if (txtIdx == textPosition) break;
		UTF8_GetAddr((unsigned char *)charSet,&offset);
		charSet+=offset;
		txtIdx++;
	}
	return charSet;
}

void VNFont::nextChar(char **txtPtr){
	unsigned char offset=0;
	UTF8_GetAddr((unsigned char *)*txtPtr,&offset);
	(*txtPtr)+=offset;
}

uint8_t VNFont::getCharBitmapRowAtY(char *charSet, int y, uint8_t byteIdx){
	unsigned char offset=0;
	uint16_t txt = UTF8_GetAddr((unsigned char *)charSet,&offset);
	unsigned int str = pgm_read_word(fontMap.f_map + txt);
	unsigned char line = pgm_read_byte( str  + fontMap.f_name - 2);
	return (uint8_t)pgm_read_byte( str + fontMap.f_name + y*line + byteIdx);
}

uint16_t VNFont::getTextLength(char *charSet){
	uint16_t textLen = 0;
	unsigned char offset=0;
	while(*charSet)
	{
		UTF8_GetAddr((unsigned char *)charSet,&offset);
		textLen++;
		charSet+=offset;
	}
	return textLen;
}

char* VNFont::getFirstVnCharOutOfWidth(char *charSet, uint8_t maxWidth){
	unsigned int textWidth = 0;
	unsigned char offset=0;
	uint16_t utf8_addr;
	while(*charSet && textWidth<maxWidth)
	{
		utf8_addr=UTF8_GetAddr((unsigned char *)charSet,&offset);
		textWidth +=getCharWidth(utf8_addr)+1;
		if (textWidth>=maxWidth) break;
		charSet+=offset;
	}
	return charSet;
}

uint8_t VNFont::getMidLine(){
	return pgm_read_byte(fontMap.f_name);
}

const VNFont VNFontTypeTahoma(tahoma10);