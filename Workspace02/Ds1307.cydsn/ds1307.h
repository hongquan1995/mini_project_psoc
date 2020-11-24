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
#ifndef DS1307_H
#define DS1307_H
#include "stdio.h"    
    

    /*Define your macro callbacks here */
    /*For more information, refer to the Writing Code topic in the PSoC Creator Help.*/
void RTC_I2C();
void DAY_DISPLAY();
void print_hour(uint8_t hour);
void print_minutes(uint8_t minutes);
void print_second(uint8_t second);
void DS1307_DISPLAY_LCD();
void SETUP_RTC();
    
#endif /* DS1307_H */   
/* [] END OF FILE */
