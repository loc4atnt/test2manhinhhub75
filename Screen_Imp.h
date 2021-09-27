template <typename RGB, unsigned int optionFlags>
void Screen<RGB,optionFlags>::align(AlignType alignType, uint8_t defaultDisplayLen, uint8_t xPadding, uint8_t yPadding){
  this->alignType = alignType;
  this->xPadding = xPadding; // align x

  // align y
  uint8_t newY0;
  uint8_t yOffsetOfAlign = 0;// for TOP_LEFT
  if (alignType==CENTER) yOffsetOfAlign = (bgLayer->getLocalHeight()-LINE_HEIGHT*lineList.size())/2;
  else if (alignType==BOTTOM_RIGHT) yOffsetOfAlign = bgLayer->getLocalHeight() - LINE_HEIGHT*lineList.size();
  for (uint8_t i = 0;i<lineList.size();i++) {
    newY0 = yPadding + yOffsetOfAlign + LINE_HEIGHT*i;
    lineList.at(i).resetLine(newY0);
    lineList.at(i).setDisplayRange(defaultDisplayLen);
  }
}

template <typename RGB, unsigned int optionFlags>
void Screen<RGB,optionFlags>::align(AlignType alignType, uint8_t xOffset, uint8_t yOffset){
	align(alignType, bgLayer->getLocalHeight(), xOffset, yOffset);
}

template <typename RGB, unsigned int optionFlags>
void Screen<RGB,optionFlags>::align(AlignType alignType){
	align(alignType, 0, 0);
}

template <typename RGB, unsigned int optionFlags>
void Screen<RGB,optionFlags>::clear(){
	for (uint8_t i = 0;i<lineList.size();i++) {
		lineList.at(i).clear();
	}
	this->lineCursor = 0;
}

template <typename RGB, unsigned int optionFlags>
void Screen<RGB,optionFlags>::hide(){
	for (uint8_t i = 0;i<lineList.size();i++) {
		lineList.at(i).hide();
	}
}

template <typename RGB, unsigned int optionFlags>
void Screen<RGB,optionFlags>::display(){
	alignTextX();
	for (uint8_t i = 0;i<lineList.size();i++) {
		lineList.at(i).display();
	}
}

template <typename RGB, unsigned int optionFlags>
void Screen<RGB,optionFlags>::attach(uint8_t lineAmount, SMLayerBackground<RGB,optionFlags> *bgLayer, MakeFont *mFont){
	this->bgLayer = bgLayer;
	this->lineCursor = 0;
	lineList.clear();
	for (int8_t i = 0;i<lineAmount;i++){
		Line<RGB,optionFlags> line;
		line.attach(1 + LINE_HEIGHT*i, bgLayer, mFont);
		lineList.push_back(line);
	}
}

template <typename RGB, unsigned int optionFlags>
uint8_t Screen<RGB,optionFlags>::getLongestLenOfLines(){
	if (lineList.size()==0) return 0;

	uint8_t longestLineIdx = 0;
	uint8_t longestLen = lineList.at(0).getPixelLen();
	uint8_t lenTemp;
	for (uint8_t i = 1;i<lineList.size();i++){
		lenTemp = lineList.at(i).getPixelLen();
		if (lenTemp>longestLen){
			longestLineIdx = i;
			longestLen = lenTemp;
		}
	}

	return longestLen;
}

template <typename RGB, unsigned int optionFlags>
void Screen<RGB,optionFlags>::alignTextX(){
	if (lineList.size()==0) return;

	uint8_t scrrenX0 = 0;

	uint8_t displayLen = getLongestLenOfLines();

	if (alignType == CENTER)
		scrrenX0 = ((bgLayer->getLocalWidth() - displayLen)/2) + xPadding;
	else if (alignType == BOTTOM_RIGHT)
		scrrenX0 = (bgLayer->getLocalWidth() - displayLen) - xPadding;
	else
		scrrenX0 = xPadding;

	for (uint8_t i = 0;i<lineList.size();i++)
		lineList.at(i).setDisplayRange(scrrenX0, displayLen);
}

template <typename RGB, unsigned int optionFlags>
void Screen<RGB,optionFlags>::setMargin(int8_t lineIdx, Margin mar, uint8_t padding){
	if (lineIdx<0)
		for (uint8_t i = 0;i<lineList.size();i++){
			lineList.at(i).setMargin(mar);
			lineList.at(i).setMarginOffset(padding);
		}
		else if (lineIdx<lineList.size()) {
			lineList.at(lineIdx).setMargin(mar);
			lineList.at(lineIdx).setMarginOffset(padding);
		}
	}

template <typename RGB, unsigned int optionFlags>
	void Screen<RGB,optionFlags>::setMargin(int8_t lineIdx, Margin mar){
		setMargin(lineIdx, mar, 0);
	}

template <typename RGB, unsigned int optionFlags>
	void Screen<RGB,optionFlags>::setMargin(Margin mar){
		setMargin(-1, mar);
	}

template <typename RGB, unsigned int optionFlags>
	bool Screen<RGB,optionFlags>::println(){
		if (lineCursor >= (lineList.size()-1)) return false;
		lineCursor++;
		return true;
	}

template <typename RGB, unsigned int optionFlags>
	void Screen<RGB,optionFlags>::printString(String str, RGB color){
		if (lineList.size() == 0) return;

		int nlIdx;
		while((nlIdx=str.indexOf('\n'))>=0){
			printNonNLString(str.substring(0, nlIdx), color);
			str.remove(0, nlIdx+1);
			println();
		}
		printNonNLString(str, color);
	}

template <typename RGB, unsigned int optionFlags>
	void Screen<RGB,optionFlags>::printNonNLString(String str, RGB color){
		if (lineList.size() == 0) return;
		int16_t printedLen;
		while(str.length()>0){
			printedLen = lineList.at(lineCursor).printString(str, color);
			if (printedLen==0 && (!println())) return;
			str.remove(0, printedLen);
		}
	}
