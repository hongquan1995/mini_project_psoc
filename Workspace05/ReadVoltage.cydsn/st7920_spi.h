#ifndef _ST7920_SPI_H_
#define _ST7920_SPI_H_
#include "cytypes.h"    
    
// ST7920 Commands

#define LCD_CLS         0x01
#define LCD_HOME        0x02
#define LCD_ADDRINC     0x06
#define LCD_DISPLAYON   0x0C
#define LCD_DISPLAYOFF  0x08
#define LCD_CURSORON    0x0E
#define LCD_CURSORBLINK 0x0F
#define LCD_BASIC       0x30
#define LCD_EXTEND      0x34
#define LCD_GFXMODE     0x36
#define LCD_TXTMODE     0x34
#define LCD_STANDBY     0x01
#define LCD_SCROLL      0x03
#define LCD_SCROLLADDR  0x40
#define LCD_ADDR        0x80
#define LCD_LINE0       0x80
#define LCD_LINE1       0x90
#define LCD_LINE2       0x88
#define LCD_LINE3       0x98    
    
    
typedef struct _propFont
{
  const uint8_t* font;
  int8_t xSize;
  uint8_t ySize;
  uint8_t firstCh;
  uint8_t lastCh;
  uint8_t minCharWd;
  uint8_t minDigitWd;
}_propFont;    
    
void ST7920_SPI_Init(void);
void ST7920_SPI_SendCmd(uint8_t byteData);
void ST7920_SPI_SendData(uint8_t b);
void ST7920_SPI_SwitchBuf(uint8_t b);
void ST7920_SPI_Display(int buf);
void ST7920_SPI_Copy(uint8_t x16, uint8_t y, uint8_t w16, uint8_t h, uint8_t buf);
void ST7920_SPI_GotoXY(uint8_t x, uint8_t y);
void ST7920_SPI_Sleep(uint8_t mode);
void ST7920_SPI_setGfxMode(uint8_t mode);
void ST7920_SPI_PrintTxt(uint8_t pos, char *str);
void ST7920_SPI_PrintTxt_(uint8_t pos, uint16_t *signs);

void ST7920_SPI_Cls(void);
void ST7920_SPI_DrawPixel(uint8_t x, uint8_t y, uint8_t col) ;
void ST7920_SPI_DrawLine(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, uint8_t col);
void ST7920_SPI_DrawLineH(uint8_t x0, uint8_t x1, uint8_t y, uint8_t col);
void ST7920_SPI_DrawLineV(uint8_t x, uint8_t y0, uint8_t y1, uint8_t col);
void ST7920_SPI_DrawLineVfast(uint8_t x, uint8_t y0, uint8_t y1, uint8_t col);
void ST7920_SPI_DrawLineVfastD(uint8_t x, uint8_t y0, uint8_t y1, uint8_t col);
void ST7920_SPI_DrawLineHfast(uint8_t x0, uint8_t x1, uint8_t y, uint8_t col);
void ST7920_SPI_DrawLineHfastD(uint8_t x0, uint8_t x1, uint8_t y, uint8_t col);
void ST7920_SPI_DrawRect(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint8_t col);
void ST7920_SPI_DrawRectD(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint8_t col);
void ST7920_SPI_FillRect(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint8_t col);
void ST7920_SPI_FillRectD(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint8_t col);
void ST7920_SPI_DrawCircle(uint8_t x0, uint8_t y0, uint8_t radius, uint8_t col);
void ST7920_SPI_FillCircle(uint8_t x0, uint8_t y0, uint8_t r, uint8_t col);
void ST7920_SPI_FillCircleD(uint8_t x0, uint8_t y0, uint8_t r, uint8_t col);


void ST7920_SPI_SetDither(uint8_t s);
int ST7920_SPI_DrawBitmap(const uint8_t *bmp, int x, uint8_t y, uint8_t w, uint8_t h);
int ST7920_SPI_DrawBitmap1(const uint8_t *bmp, int x, uint8_t y);
void ST7920_SPI_SetFont(const uint8_t* font);
unsigned char ST7920_SPI_ConvertPolish(unsigned char _c);
int ST7920_SPI_CharWidth(uint8_t c, uint8_t last);
int ST7920_SPI_StrWidth(char *str);
int ST7920_SPI_PrintChar(int xpos, int ypos, unsigned char c);
int ST7920_SPI_PrintStr(int xpos, int ypos, char *str);
void ST7920_SPI_PrintTxt(uint8_t pos, char *str);
void ST7920_SPI_PrintTxt_(uint8_t pos, uint16_t *signs);


#endif
    