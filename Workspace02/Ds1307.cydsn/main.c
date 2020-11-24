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
#include "main.h"
#include "stdio.h"
#include "stdlib.h"
#include "ds1307.h"

const uint8 sevenSeg[12] = {0xFC, 0x60, 0xDA, 0xF2, 0x66, 0xB6, 0xBE, 0xE0, 0xFE, 0xF6, 0xC6, 0x9C};
/*thousand = count/1000;
  hundred = (count%1000)/100;
  dozen = (count%100)/10;
  unit = count%10;*/
//uint16 msTicks = 0;
uint16_t vr_timer_7seg = 0;
uint16_t vr_timer_temp = 0;
uint16_t vr_timer_count = 0;
int value;
int temp;
int vrCnv;
uint8_t flag_timer = 0;
uint8_t flag_count = 0;

uint8_t vr_led_7_1;
uint8_t vr_led_7_2;
uint8_t vr_led_7_3;
uint8_t vr_led_7_4;

extern uint8 Table[];
//quandh
CY_ISR(MY_ISR) {// interrupt timer for 7seg
    vr_timer_7seg++;
    vr_timer_temp++;
    vr_timer_count++;
    if(vr_timer_count == 100){
        flag_count = 1;
        vr_timer_count = 0;
    }
    if(vr_timer_temp == 5000){
        flag_timer ++;
        vr_timer_temp = 0;
    }
    if(vr_timer_7seg == 1){
        led_scan(vr_led_7_1, 0);
    }
    if(vr_timer_7seg == 2){
        led_scan(vr_led_7_2, 1);
    }
    if(vr_timer_7seg == 3){
        led_scan(vr_led_7_3, 2);
    }
    if(vr_timer_7seg == 4){
        led_scan(vr_led_7_4, 3); 
        vr_timer_7seg = 0;
    }
    
    Timer_1_ClearInterrupt(Timer_1_INTR_MASK_TC);
}

char Data;
uint8 indexBuffer;
char Buffer[50];
uint8_t vrUart;
uint8_t flag_uart = 0;

CY_ISR(RX_ISR){
    uint8 sub;
    Data = UART_GetChar();
    Buffer[indexBuffer] = Data;
    indexBuffer++;
    if (Data == '\r'){
        flag_uart = 1;
    }
}

void led_scan(uint8_t number, uint8_t pos) // func scan led
{
    Pin_Ctrl_Write(~(1<<pos));
    Pin_7Seg_Write(sevenSeg[number]);

}

/*convert Decimal to BCD*/
uint8_t convertDecToBCD(uint8_t vrDec) {
	uint8_t vrBCD;
	vrBCD = 0xF0 & ((vrDec/10) << 4);
	vrBCD |= vrDec%10;
	return vrBCD;
}

int main(void)
{
    Timer_1_Start(); // Configure and enable timer
    isr_1_StartEx(MY_ISR); // setup timer interrupt sub-routine
    isr_rx_StartEx(RX_ISR);
    LCD_Start();
    LCD_ClearDisplay();  
    ADC_Start();
    I2C_Start();
    SETUP_RTC();
    ADC_StartConvert();
    UART_Start();
    
    CyGlobalIntEnable; /* Enable global interrupts. */
       
    vr_led_7_1 = Table[1]&0x0F;
    vr_led_7_2 = Table[1]>>4;
    vr_led_7_3 = Table[2]&0X0F;
    vr_led_7_4 = (Table[2]>>4)&0x03;

    for(;;)
    {
        /* Place your application code here. */
        if(flag_count == 1){
            RTC_I2C();
            DS1307_DISPLAY_LCD();
            flag_count = 0;
        }
              
        if(ADC_IsEndConversion(ADC_RETURN_STATUS)){
        value = ADC_CountsTo_mVolts(0,ADC_GetResult16(0));
        }
        temp = value/10;
        vrCnv = convertDecToBCD(temp);
        if(flag_timer == 1){
            vr_led_7_1 = 11;
            vr_led_7_2 = 10;
            vr_led_7_3 = vrCnv&0x0F;
            vr_led_7_4 = vrCnv>>4;
        }
         if(flag_timer == 2){
            vr_led_7_1 = Table[1]&0x0F;
            vr_led_7_2 = Table[1]>>4;
            vr_led_7_3 = Table[2]&0X0F;
            vr_led_7_4 = (Table[2]>>4)&0x03; 
            flag_timer = 0;
        }
        
        if(flag_uart == 1){
            indexBuffer = 0;
            vrUart = atoi(Buffer);
            //UART_PutString(Buffer);
            flag_uart = 0;
            indexBuffer = 0;
            if(vrUart < temp){
                UART_PutString("10khz");
                PWM_1_Start();
                PWM_2_Stop();
             }
             else{
                UART_PutString("50khz");
                PWM_2_Start();
                PWM_1_Stop();
             }
        }      
    }
}

/* [] END OF FILE */
