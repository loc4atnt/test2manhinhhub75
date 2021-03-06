/*
  FontMaker.cpp - Thư viện Font tương thích utf-8
  Created by Dao Nguyen - IOT47.com
  Liên hệ: daonguyen20798@gmail.com
  Người dùng toàn quyền sử dụng cho mục đích cá nhân
*/
#include "FontMaker.h"

MakeFont::MakeFont(set_px_typedef set_px)
{
	FontMaker_setpx = set_px;
}

void MakeFont::setFont(const VNFont *newFont)
{
   this->font = (VNFont*)newFont;
}

unsigned char MakeFont::read(int16_t x, int16_t y,  uint16_t txt)
{
    unsigned char temp = x % 8;
    unsigned char x1 = 0x80 >> temp;
    unsigned int str = pgm_read_word(this->font->fontMap.f_map + txt);
    unsigned char line = pgm_read_byte( str  + this->font->fontMap.f_name - 2);
    return pgm_read_byte( str + this->font->fontMap.f_name + y*line +x/8  )& x1;
}
unsigned char MakeFont::putChar(int16_t x,int16_t y,uint16_t txt,uint16_t color,uint16_t backcolor)
{
    unsigned int str = pgm_read_word(this->font->fontMap.f_map + txt);
    int size_w = pgm_read_byte( str  + this->font->fontMap.f_name - 4); //lấy chiều rộng Font
    int size_h = pgm_read_byte( str  + this->font->fontMap.f_name - 3); //lấy chiều cao Font 
    int mid_line = pgm_read_byte(this->font->fontMap.f_name); //lấy mid line - đường cơ bản

    int start_y=pgm_read_byte( str  + this->font->fontMap.f_name - 1);
    if (start_y>0) start_y+=1;
    
    int offset = pgm_read_byte( str  + this->font->fontMap.f_name - 2);
    // if(size_h < mid_line)start_y=mid_line-size_h;
    start_y+=(mid_line-size_h);
    for(int i=0;i<size_w;i++)
        for(int h=0;h<size_h;h++)
            if(read(i,h,txt) != 0)
                FontMaker_setpx(i+x,h+y+start_y,color);
            else FontMaker_setpx(i+x,h+y+start_y,backcolor);
    return size_w;
}
void MakeFont::print(int16_t x,int16_t y,unsigned char *s,uint16_t color,uint16_t backcolor)
{
   unsigned char offset=0;
   uint16_t utf8_addr;
   while(*s)
   {
      utf8_addr=UTF8_GetAddr(s,&offset);
      x +=putChar(x,y,utf8_addr,color,backcolor)+1;
      s+=offset;
   }
}
void MakeFont::print(int16_t x,int16_t y,char *s,uint16_t color,uint16_t backcolor)
{
   unsigned char offset=0;
   uint16_t utf8_addr;
   while(*s)
   {
      utf8_addr=UTF8_GetAddr((unsigned char *)s,&offset);
      x +=putChar(x,y,utf8_addr,color,backcolor)+1;
      s+=offset;
   }
}
void MakeFont::print(int16_t x,int16_t y,String str,uint16_t color,uint16_t backcolor)
{
   unsigned char offset=0;
   uint16_t utf8_addr;
   unsigned char *s = (unsigned char*)&str[0];
   while(*s)
   {
      utf8_addr=UTF8_GetAddr((unsigned char *)s,&offset);
      x +=putChar(x,y,utf8_addr,color,backcolor)+1;
      s+=offset;
   }
}
unsigned char MakeFont::putChar_noBackColor(int16_t x,int16_t y,uint16_t txt,uint16_t color)
{
    unsigned int str = pgm_read_word(this->font->fontMap.f_map + txt);
    int size_w = pgm_read_byte( str  + this->font->fontMap.f_name - 4); //lấy chiều rộng Font
    int size_h = pgm_read_byte( str  + this->font->fontMap.f_name - 3); //lấy chiều cao Font 
    int mid_line = pgm_read_byte(this->font->fontMap.f_name); //lấy mid line - đường cơ bản

    int start_y=pgm_read_byte( str  + this->font->fontMap.f_name - 1);
    if (start_y>0) start_y+=1;

    int offset = pgm_read_byte( str  + this->font->fontMap.f_name - 2);
    // if(size_h < mid_line)start_y=mid_line-size_h;
    start_y+=(mid_line-size_h);
    for(int i=0;i<size_w;i++)
        for(int h=0;h<size_h;h++)
            if(read(i,h,txt) != 0)
                FontMaker_setpx(i+x,h+y+start_y,color);
    return size_w;
}
void MakeFont::print_noBackColor(int16_t x,int16_t y,unsigned char *s,uint16_t color)
{
   unsigned char offset=0;
   uint16_t utf8_addr;
   while(*s)
   {
      utf8_addr=UTF8_GetAddr(s,&offset);
      x +=putChar_noBackColor(x,y,utf8_addr,color)+1;
      s+=offset;
   }
}
void MakeFont::print_noBackColor(int16_t x,int16_t y,char *s,uint16_t color)
{
   unsigned char offset=0;
   uint16_t utf8_addr;
   while(*s)
   {
      utf8_addr=UTF8_GetAddr((unsigned char *)s,&offset);
      x +=putChar_noBackColor(x,y,utf8_addr,color)+1;
      s+=offset;
   }
}
void MakeFont::print_noBackColor(int16_t x,int16_t y,String str,uint16_t color)
{
   unsigned char offset=0;
   uint16_t utf8_addr;
   unsigned char *s = (unsigned char*)&str[0];
   while(*s)
   {
      utf8_addr=UTF8_GetAddr((unsigned char *)s,&offset);
      x +=putChar_noBackColor(x,y,utf8_addr,color)+1;
      s+=offset;
   }
}
//----------------------------------------------END FILE--------------------------------------------------//
