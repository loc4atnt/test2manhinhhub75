#ifndef _Line_H_
#define _Line_H_

#include <stdint.h>
#include "src/SmartMatrix/FontMaker/FontMaker.h"
#include "src/SmartMatrix/SmartMatrix.h"
#include <vector>

#define STRIP_0 1
#define STRIP_1 17
#define STRIP_2 33
#define STRIP_3 49

#define LINE_HEIGHT 16
// #define LEAST_EMPTY_PIXEL_LEN 10

enum Margin {
	MIDDLE, LEFT, RIGHT
};

template <typename RGB, unsigned int optionFlags>
class Line {
public:
	~Line();
	void attach(uint8_t y0, SMLayerBackground<RGB,optionFlags> *bgLayer, MakeFont *mFont);
	void setMargin(Margin marType);
	void setMarginOffset(uint8_t marOffset);
	uint8_t getOriginalY();
	Margin getMarginType();
	uint8_t getMarginOffset();
	int16_t printString(String str, RGB color);
	void clear();
	void display();
	void resetLine(uint8_t newY0);
	uint8_t getPixelLen();
	uint8_t getMaxPixelLen();
	void hide();


  	void setDisplayRange(uint8_t x0, uint8_t rangeLen);
   void setDisplayRange(uint8_t rangeLen);
private:
	SMLayerBackground<RGB,optionFlags> *bgLayer;
	MakeFont *makeFont;
	uint8_t originalY = -1;
	Margin marginType = LEFT;
	uint8_t marginOffset = 0;
  uint8_t x0OfRange = 0;
  uint8_t lenOfRange = 64;

	String buffer = "";
	std::vector<uint8_t> splitColorIdexes;
	std::vector<RGB> colorArr;

	uint8_t calXCoordinate(String str);
};

#include "Line_Imp.h"

#endif
