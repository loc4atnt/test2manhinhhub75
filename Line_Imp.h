template <typename RGB, unsigned int optionFlags>
Line<RGB,optionFlags>::~Line(){
	clear();
}

template <typename RGB, unsigned int optionFlags>
void Line<RGB,optionFlags>::attach(uint8_t y0, SMLayerBackground<RGB,optionFlags> *bgLayer, MakeFont *mFont){
	this->originalY = y0;
	this->bgLayer = bgLayer;
	this->makeFont = mFont;
	clear();// clear voi setting moi
}

template <typename RGB, unsigned int optionFlags>
void Line<RGB,optionFlags>::setMargin(Margin marType){
	this->marginType = marType;
}

template <typename RGB, unsigned int optionFlags>
void Line<RGB,optionFlags>::setMarginOffset(uint8_t marOffset){
	this->marginOffset = marOffset;
}

template <typename RGB, unsigned int optionFlags>
uint8_t Line<RGB,optionFlags>::getOriginalY(){return this->originalY;}

template <typename RGB, unsigned int optionFlags>
Margin Line<RGB,optionFlags>::getMarginType(){return this->marginType;}

template <typename RGB, unsigned int optionFlags>
uint8_t Line<RGB,optionFlags>::getMarginOffset(){return this->marginOffset;}

template <typename RGB, unsigned int optionFlags>
int16_t Line<RGB,optionFlags>::printString(String str, RGB color){
	// if ((getMaxPixelLen()-makeFont->font->getTextWidth(buffPtr))<=LEAST_EMPTY_PIXEL_LEN){
	// 	clear();
	// 	printString(str, color);
	// 	return;
	// }

	uint8_t lastBuffLen = buffer.length();
	buffer+=str;
  char *buffPtr = (char*)buffer.c_str();
  int spaceTrimAmount = 0;
	if (makeFont->font->getTextWidth(buffPtr)>getMaxPixelLen()){
		int maxBuffLen = (int)(makeFont->font->getFirstVnCharOutOfWidth(buffPtr, getMaxPixelLen()) - buffPtr);
    while (buffer.charAt(maxBuffLen - spaceTrimAmount - 1)==' ') spaceTrimAmount++;
		buffer.remove(maxBuffLen-spaceTrimAmount);
    for (int k = 0;k<spaceTrimAmount;k++) buffer = " " + buffer;
	}
	
	splitColorIdexes.push_back(lastBuffLen);
	colorArr.push_back(color);
	return (buffer.length() - lastBuffLen);
}

template <typename RGB, unsigned int optionFlags>
uint8_t Line<RGB,optionFlags>::calXCoordinate(String str){
	if (marginType==LEFT)
		return x0OfRange + marginOffset;

	uint8_t pixelWidth = this->makeFont->font->getTextWidth((char*)str.c_str());
	if (marginType==MIDDLE)
		return x0OfRange + ((this->lenOfRange - pixelWidth)/2) + marginOffset;
	else
		return x0OfRange + (this->lenOfRange - pixelWidth - marginOffset);
}

template <typename RGB, unsigned int optionFlags>
void Line<RGB,optionFlags>::display(){
	hide();

	String subBuff;
	uint8_t xIndex = calXCoordinate(this->buffer);
	for (uint8_t i =0;i<splitColorIdexes.size();i++){
		if (i<(splitColorIdexes.size()-1))
			subBuff = this->buffer.substring(splitColorIdexes.at(i), splitColorIdexes.at(i+1));
		else subBuff = this->buffer.substring(splitColorIdexes.at(i));
		makeFont->print_noBackColor(xIndex,originalY,(char*)subBuff.c_str(),colorArr.at(i).rgb);
		xIndex+=makeFont->font->getTextWidth((char*)subBuff.c_str());
	}
	bgLayer->swapBuffers();
}

template <typename RGB, unsigned int optionFlags>
void Line<RGB,optionFlags>::hide(){
	bgLayer->fillRectangle(0, originalY, bgLayer->getLocalWidth(), originalY+LINE_HEIGHT-1, {0,0,0});
	bgLayer->swapBuffers();
}

template <typename RGB, unsigned int optionFlags>
void Line<RGB,optionFlags>::clear(){
	this->buffer = "";
	splitColorIdexes.clear();
	colorArr.clear();
	hide();
}

template <typename RGB, unsigned int optionFlags>
void Line<RGB,optionFlags>::resetLine(uint8_t newY0){
	hide();
	this->originalY = newY0;
	display();
}

template <typename RGB, unsigned int optionFlags>
uint8_t Line<RGB,optionFlags>::getPixelLen(){
	return makeFont->font->getTextWidth((char*)buffer.c_str());
}

template <typename RGB, unsigned int optionFlags>
uint8_t Line<RGB,optionFlags>::getMaxPixelLen(){
	return this->lenOfRange;
}

template <typename RGB, unsigned int optionFlags>
void Line<RGB,optionFlags>::setDisplayRange(uint8_t x0, uint8_t rangeLen){
  this->x0OfRange = x0;
  this->lenOfRange = rangeLen;
}

template <typename RGB, unsigned int optionFlags>
void Line<RGB,optionFlags>::setDisplayRange(uint8_t rangeLen){
  setDisplayRange(0, rangeLen);
}

// template <typename RGB, unsigned int optionFlags>
// uint8_t Line<RGB,optionFlags>::getEmptyPxLen(){
// 	return getMaxPixelLen() - getPixelLen();
// }
