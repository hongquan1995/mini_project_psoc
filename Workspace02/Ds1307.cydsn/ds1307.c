/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include "project.h"
#include "stdio.h"

 ///RTC variables/////
#define SlaveAddress 0x68
uint8 Table[7];
#define MON 1
#define TUES 2
#define WEN 3
#define THUS 4
#define FRI 5
#define SAT 6
#define SUN 7

/*typedef struct{
   uint8_t second;
   uint8_t minute;
   uint8_t hour;
   uint8_t day;
   uint8_t date;
   uint8_t month;
   uint16_t year;
}RTC_t;

RTC_t rtcTime = 
{
    .second = 0x00,
    .minute = 0x08,
    .hour = 0x04,
    .day = 0x04,
    .date = 0x18,
    .month = 0x11,
    .year = 0x20,
};*/

////RTC   ///////
void RTC_I2C(){
    uint8 result,i;
        do{
           result=I2C_I2CMasterSendStart(SlaveAddress, I2C_I2C_WRITE_XFER_MODE, 1000);
        }
        while(result!=I2C_I2C_MSTR_NO_ERROR);
        
        result=I2C_I2CMasterWriteByte(0x00, 1000);
        result=I2C_I2CMasterSendRestart(SlaveAddress, I2C_I2C_READ_XFER_MODE, 1000);
        for(i=0;i<6;i++){
            I2C_I2CMasterReadByte(I2C_I2C_ACK_DATA, &Table[i], 1000);
        }
            I2C_I2CMasterReadByte(I2C_I2C_NAK_DATA, &Table[6],1000);
        I2C_I2CMasterSendStop(1000);       
}

void DAY_DISPLAY(){
    switch(Table[3]){
        case MON:
            LCD_PrintString("MON");
            break;
        case TUES:
            LCD_PrintString("TUES");
            break;
        case WEN:
            LCD_PrintString("WEN");
            break;
        case THUS:
            LCD_PrintString("THUS");
            break;
        case FRI:
            LCD_PrintString("FRI");
            break;
        case SAT:
            LCD_PrintString("SAT");
            break;
        case SUN:
            LCD_PrintString("SUN");
            break;
        default: 
            LCD_PrintString("MON");
            break;    
    }
}

void print_hour(uint8_t hour){
    LCD_PrintNumber((hour>>4)&0x03);   
    LCD_PrintNumber(hour&0X0F);
}

void print_minutes(uint8_t minutes){
    LCD_PrintNumber(minutes>>4);    
    LCD_PrintNumber(minutes&0x0F);
}

void print_second(uint8_t second){
    LCD_PrintNumber(second>>4&0x07);    
    LCD_PrintNumber(second&0x0F);
}

void print_yearMonthDay(uint8_t value){
    LCD_PrintNumber(value>>4);
    LCD_PrintNumber(value&0x0F);
}
void DS1307_DISPLAY_LCD(){
    LCD_ClearDisplay();
    LCD_Position(0,0);
    print_hour(Table[2]);   // hour 
    LCD_PutChar(':');
    print_minutes(Table[1]);    // minutes
    LCD_PutChar(':');
    print_second(Table[0]); // Second


    LCD_Position(1,0);
    LCD_PrintString("20");
    print_yearMonthDay(Table[6]); //year
    LCD_PutChar('/');
    print_yearMonthDay(Table[5]); //month
    LCD_PutChar('/');
    print_yearMonthDay(Table[4]);   //day
    LCD_PutChar(' '); 
    DAY_DISPLAY();
}

void SETUP_RTC(){
    uint8 result,i;

    Table[0]=0x01;//second
    Table[1]=0x08;//minute
    Table[2]=0x04;//hour
    Table[3]=0x04;//day .
    Table[4]=0x18;//date
    Table[5]=0x11;//month
    Table[6]=0x20;//year
        
      do{
           result=I2C_I2CMasterSendStart(SlaveAddress, I2C_I2C_WRITE_XFER_MODE, 1000);
      }
      while(result!=I2C_I2C_MSTR_NO_ERROR);
        
      result=I2C_I2CMasterWriteByte(0x0,1000);
     for(i=0;i<7;i++){
            result=I2C_I2CMasterWriteByte(Table[i],1000);
      
    }
      I2C_I2CMasterSendStop(1000);
}
/* [] END OF FILE */
