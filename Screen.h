#ifndef _Screen_H_
#define _Screen_H_

#include "Line.h"

enum AlignType {
	CENTER, TOP_LEFT, BOTTOM_RIGHT
};

// struct Cursor {
// 	uint8_t lineIdx;
// 	uint8_t pxLenInLine;
// }

template <typename RGB, unsigned int optionFlags>
class Screen {
public:
	void attach(uint8_t lineAmount, SMLayerBackground<RGB,optionFlags> *bgLayer, MakeFont *mFont);
  void align(AlignType alignType, uint8_t defaultDisplayLen, uint8_t xPadding, uint8_t yPadding);
	void align(AlignType alignType, uint8_t xPadding, uint8_t yPadding);
	void align(AlignType alignType);
	void setMargin(int8_t lineIdx, Margin mar, uint8_t padding);
	void setMargin(int8_t lineIdx, Margin mar);
	void setMargin(Margin mar);
	void printString(String str, RGB color);
	void clear();
	void hide();
	void display();
	bool println();
private:
	SMLayerBackground<RGB,optionFlags> *bgLayer;
	std::vector<Line<RGB,optionFlags>> lineList;
	AlignType alignType = TOP_LEFT;
	int8_t lineCursor = 0;

	uint8_t xPadding = 0;

	void alignTextX();
	void printNonNLString(String str, RGB color);
  uint8_t getLongestLenOfLines();
};

#include "Screen_Imp.h"

#endif
