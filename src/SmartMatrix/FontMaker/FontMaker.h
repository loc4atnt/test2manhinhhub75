/*
  FontMaker.h - Thư viện Font tương thích utf-8
  Created by Dao Nguyen - IOT47.com
  Liên hệ: daonguyen20798@gmail.com
  Người dùng toàn quyền sử dụng cho mục đích cá nhân
*/
#ifndef __FontMaker_h___
#define __FontMaker_h___

#include "IOT47_UTF8.h"
#include "MyFontMaker.h"
#include "VNFont/VNFont.h"

typedef void (*set_px_typedef)(int16_t x,int16_t y,uint16_t color);  
class MakeFont
{
    public:     
   	unsigned char read(int16_t x, int16_t y,  uint16_t txt);
   	unsigned char putChar(int16_t x,int16_t y,uint16_t txt,uint16_t color,uint16_t backcolor);
    unsigned char putChar_noBackColor(int16_t x,int16_t y,uint16_t txt,uint16_t color);
   	void print(int16_t x,int16_t y,unsigned char *s,uint16_t color,uint16_t backcolor);
   	void print(int16_t x,int16_t y,char *s,uint16_t color,uint16_t backcolor);
    void print(int16_t x,int16_t y,String str,uint16_t color,uint16_t backcolor);
    void print_noBackColor(int16_t x,int16_t y,unsigned char *s,uint16_t color);
    void print_noBackColor(int16_t x,int16_t y,char *s,uint16_t color);
    void print_noBackColor(int16_t x,int16_t y,String str,uint16_t color);
    void setFont(const VNFont *font);
   	MakeFont(set_px_typedef set_px);
    VNFont *font;
   	private:
    set_px_typedef FontMaker_setpx;
};

#endif //__FontMaker_h___
