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
  screen1.printString("IN D??I H???T B???NG LU??N N?? HEHE", {7,0,0});
  screen1.display();
  while(true);
//  delay(4000);
//  screen1.clear();
//  screen1.align(CENTER, 16, 8);
//  screen1.setMargin(LEFT);
//  screen1.printString("Xin ch??o c??c b???n!\nCh??ng t??i ??ang code b???ng led RGB ????? ph??n gi???i 32*64, ch??? ????? ti???ng vi???t, nhi???u d??ng", mauC[2]);
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
  scrollingLayer.start("Tr??m n??m trong c??i ng?????i ta, Ch??? t??i ch??? m???nh kh??o l?? gh??t nhau. Tr???i qua m???t cu???c b??? d??u, Nh???ng ??i???u tr??ng th???y m?? ??au ?????n l??ng. L??? g?? b??? s???c t?? phong, Tr???i xanh quen v???i m?? h???ng ????nh ghen*.", -1);
//  scrollingLayer.start("C??c b???n ??i, ch??? ??ang t???ng h???p s??? li???u sinh vi??n c?? th??? BIDV, c??c b???n vui l??ng tr??? l???i ch??? bi???t b???n n??o ??ang s??? d???ng th??? tr???ng, b???n n??o s??? d???ng th??? BIDV, C???m ??n c??c b???n. Ch??c c??c b???n vui! V?? bu???i t???i vui v??? hheheh :??", -1);
//  scrollingLayer.start("C??c b???n ??i, ch??? ??ang t???ng h???p s??? li???u sinh vi??n c?? th??? BIDV, c??c b???n vui l??ng tr??? l???i ch??? bi???t b???n n??o ??ang s??? d???ng th??? tr???ng, b???n n??o s??? d???ng th??? BIDV, (v?? d???: Nguy???n V??n A P101 th??? tr???ng, ho???c nguy???n v??n B p102 th??? BIDV).C???m ??n c??c b???n.", -1);
//scrollingLayer.start("Ch??c qu?? kh??ch c?? m???t chuy???n ??i vui v???, m???t ng??y m???i t???t l??nh", -1);
}
