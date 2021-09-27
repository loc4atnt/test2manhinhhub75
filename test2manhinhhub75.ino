#include "src/SmartMatrix/MatrixHardware_ESP32_V0.h"
#include "src/SmartMatrix/SmartMatrix.h"

#include "src/SmartMatrix/FontMaker/FontMaker.h"
#include "Screen.h"

#define COLOR_DEPTH  8
const uint16_t kMatrixWidth = 192;
const uint16_t kMatrixHeight = 64;
const uint8_t kRefreshDepth = 24;       // Tradeoff of color quality vs refresh rate, max brightness, and RAM usage.  36 is typically good, drop down to 24 if you need to.  On Teensy, multiples of 3, up to 48: 3, 6, 9, 12, 15, 18, 21, 24, 27, 30, 33, 36, 39, 42, 45, 48.  On ESP32: 24, 36, 48
const uint8_t kDmaBufferRows = 2;       // known working: 2-4, use 2 to save RAM, more to keep from dropping frames and automatically lowering refresh rate.  (This isn't used on ESP32, leave as default)
const uint8_t kPanelType = SMARTMATRIX_HUB75_32ROW_64COL_MOD8SCAN;
//const uint32_t kMatrixOptions = (SM_HUB75_OPTIONS_MATRIXCALC_LOWPRIORITY|SM_HUB75_OPTIONS_ESP32_CALC_TASK_CORE_1);        // see docs for options: https://github.com/pixelmatix/SmartMatrix/wiki
const uint32_t kMatrixOptions = (SM_HUB75_OPTIONS_NONE);        // see docs for options: https://github.com/pixelmatix/SmartMatrix/wiki
const uint8_t kBackgroundLayerOptions = (SM_BACKGROUND_OPTIONS_NONE);
const uint8_t kScrollingLayerOptions = (SM_SCROLLING_OPTIONS_NONE);

SMARTMATRIX_ALLOCATE_BUFFERS(matrix, kMatrixWidth, kMatrixHeight, kRefreshDepth, kDmaBufferRows, kPanelType, kMatrixOptions);
SMARTMATRIX_ALLOCATE_BACKGROUND_LAYER(backgroundLayer, kMatrixWidth, kMatrixHeight, COLOR_DEPTH, kBackgroundLayerOptions);
SMARTMATRIX_ALLOCATE_VN_SCROLLING_LAYER(scrollingLayer, kMatrixWidth, kMatrixHeight, COLOR_DEPTH, kScrollingLayerOptions);

const int defaultBrightness = 255;        // full (100%) brightness
const rgb8 defaultBackgroundColor(0, 0, 0);

rgb8 mauC[4] = {{0, 5, 0}, {5, 5, 0}, {0, 1, 3}, {5, 0, 0}};

void setPX(int16_t x, int16_t y, uint16_t color)
{
  rgb8 colorRGB;
  colorRGB.rgb = color;
  backgroundLayer.drawPixel(x, y, colorRGB);
}

MakeFont makeFont(&setPX);

Screen<rgb8,kBackgroundLayerOptions> screen1;

void setup() {
  Serial.begin(115200);
  makeFont.setFont(&VNFontTypeTahoma);
  
  matrix.addLayer(&backgroundLayer);
  matrix.addLayer(&scrollingLayer);
  matrix.begin();
  matrix.setBrightness(defaultBrightness);

  backgroundLayer.enableColorCorrection(false);
  scrollingLayer.enableColorCorrection(false);

  backgroundLayer.fillScreen(defaultBackgroundColor);
  backgroundLayer.swapBuffers();

  screen1.attach(3, &backgroundLayer, &makeFont);// 3 => so dong
  screen1.align(CENTER, 160, 0, 0);
  screen1.setMargin(MIDDLE);

  scrollVinBusTitle();
}

void loop() {
  screen1.clear();
//  screen1.align(CENTER, 8, 0);
//  screen1.setMargin(MIDDLE);
  screen1.printString("HAPPY NEW YEAR", {7,0,0});
  screen1.printString(" 2021 ", {7,7,0});
  screen1.printString("IN DÀI HẾT BẢNG LUÔN NÈ HEHE", {7,0,0});
  screen1.display();
  while(true);
//  delay(4000);
//  screen1.clear();
//  screen1.align(CENTER, 16, 8);
//  screen1.setMargin(LEFT);
//  screen1.printString("Xin chào các bạn!\nChúng tôi đang code bảng led RGB độ phân giải 32*64, chế độ tiếng việt, nhiều dòng", mauC[2]);
//  screen1.display();
//  delay(4000);
}

//void testFoo(){
//  Line<rgb8,kBackgroundLayerOptions> screen;
//  screen.attach(STRIP_3, &backgroundLayer, &makeFont);
//  screen.setMargin(CENTER);
//  list.push_back(screen);
//}

void db(String label, String val){
  Serial.print(label);
  Serial.print(": ");
  Serial.println(val);
}

void scrollVinBusTitle(){
  makeFont.print_noBackColor(0,0,"VinBus |",mauC[3].rgb);
  backgroundLayer.swapBuffers();

  scrollingLayer.setOffsetFromTop(0);
  scrollingLayer.setStartOffsetFromLeft(0);
  scrollingLayer.setOriginalX(50);
  scrollingLayer.setColor({0,6,2});
  scrollingLayer.setMode(wrapForward);
  scrollingLayer.setSpeed(40);
  scrollingLayer.start("Trăm năm trong cõi người ta, Chữ tài chữ mệnh khéo là ghét nhau. Trải qua một cuộc bể dâu, Những điều trông thấy mà đau đớn lòng. Lạ gì bỉ sắc tư phong, Trời xanh quen với má hồng đánh ghen*.", -1);
//  scrollingLayer.start("Các bạn ơi, chị đang tổng hợp số liệu sinh viên có thẻ BIDV, các bạn vui lòng trả lời chị biết bạn nào đang sử dụng thẻ trắng, bạn nào sử dụng thẻ BIDV, Cảm ơn các bạn. Chúc các bạn vui! Và buổi tối vui vẻ hheheh :Đ", -1);
//  scrollingLayer.start("Các bạn ơi, chị đang tổng hợp số liệu sinh viên có thẻ BIDV, các bạn vui lòng trả lời chị biết bạn nào đang sử dụng thẻ trắng, bạn nào sử dụng thẻ BIDV, (ví dụ: Nguyễn Văn A P101 thẻ trắng, hoặc nguyễn văn B p102 thẻ BIDV).Cảm ơn các bạn.", -1);
//scrollingLayer.start("Chúc quý khách có một chuyến đi vui vẻ, một ngày mới tốt lành", -1);
}
