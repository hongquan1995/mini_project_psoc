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
#include "string.h"
#include "trace.h"
#include "math.h"
#include "PowerAnalyzer.h"
#include "st7920_spi.h"
#include "c64enh_font.h"

#define INTERRUPT_TIMER     (1.0/12000000.0) * Timer_1_TC_PERIOD_VALUE
#define VOLTAGE_FACTOR     1.102586
#define CURRENT_RATIO      0.125
#define U_ADC               0
#define N_ADC               1
#define V_ADC               2
#define W_ADC               3
#define X1_ADC              4
#define L3_ADC              5
#define NL_ADC              6
#define I3_ADC              7


uint8 channel_ADC[] = {U_ADC, N_ADC, V_ADC, W_ADC};
uint32 timer_count = 0;

uint32 over_step = 0;
int32 adc_freq;

int32 adc_curr;
int16 vr_index = 0;
uint16 temp_period = 0;
uint16 tick_period;
int16 arrADC[5];

volatile uint8 enable_read_frequency = 0;
uint8 complete_read_frequency = 0;
uint8 flag_frequency = 0;
uint8 check_freq = 0;
uint8 check_time_freq = 0;

float period;
uint16 tick_period;
float frequency;
float avg_freq = 0;

uint8 flag_adc_volt;

float rms_voltP1 = 0;
float rms_voltP2 = 0;
float rms_voltP3 = 0;

float rms_voltG1 = 0;
float rms_voltG2 = 0;
float rms_voltG3 = 0;
float rms_curPA = 0;
float power_factor = 0;

int32 real_power = 0;

void select_mux_pin(uint8 S2, uint8 S1, uint8 S0){
   MUX_A_Write(S0);
   MUX_B_Write(S1);
   MUX_C_Write(S2);

}

void enable_read_freq(){
    enable_read_frequency = 1;
}

void wait_for_read_freq(){
    while (complete_read_frequency == 0){};
    enable_read_frequency = 0;
}

void start_read_adc(){
    flag_adc_volt = 1;
    check_time_freq = 0;
}

void RMS_Current(float *current){
    *current = *current* CURRENT_RATIO;
}

// đọc ADC giá trị điện áp 3 pha máy phát điện
void Read_ADC_generator_voltage(int16 adc_vol[4][500], uint8 channel, uint16 count){
    adc_vol[channel][count] = ADC_Read(channel);
}

// tính trung bình cộng giá trị offset
void total_value_offset(int16 adc_vol[4][500], int32 vol_offset_sum[], uint16 count, uint8 len, int16 vol_offset[]){
    for(uint8 i = 0; i < len; i++){
        for(uint16 j = count-1; j >= 0 ; j--){
            vol_offset_sum[i] += adc_vol[i][count];    
        }
        vol_offset[i] = vol_offset_sum[i]/count;
    }
}

// tinh tích phân giá trị điện áp từng pha
void read_integral_voltage(int16 adc_vol[4][500], int16 vol_offset[], uint16 count, uint8 len, int32 vol_sq_sum[], float rms_volt[]){
    for(uint8 i = 0; i < len; i++){
        for(uint16 j = 0; j < count; j++)
        {
            adc_vol[i][j] = adc_vol[i][j] - vol_offset[i];  
            vol_sq_sum[i] = vol_sq_sum[i] + adc_vol[i][j] * adc_vol[i][j];
        }
     vol_sq_sum[i] = vol_sq_sum[i] / count; 
     rms_volt[i] = sqrt(vol_sq_sum[i]);
    }
}

void RMS_Voltage_Phase(float *rms_voltA, float *rms_voltB, float *rms_voltC){
    int16 adc_vol[4][500]; //adc_volU, adc_volN, adc_volV, adc_volW
    int32 vol_offset_sum[4];    //volU_offset_sum, volV_offset_sum, volW_offset_sum, volN_offset_sum, 
    int16 vol_offset[4];    //  volU_offset = 0, volV_offset = 0, volW_offset = 0, volN_offset = 0
    int32 vol_sq_sum[4];    //volU_sq_sum = 0, volV_sq_sum = 0, volW_sq_sum = 0, volN_sq_sum = 0
    float rms_volt[4];      //rms_voltU = 0, rms_voltV = 0, rms_voltW = 0, rms_voltN = 0;
    uint16 count = 0;
    
    // lấy ADC trong 1 chu kỳ
    while(check_time_freq < tick_period){
        for(uint8 i = 0; i < sizeof(channel_ADC); i++){
            Read_ADC_generator_voltage(&adc_vol[i], channel_ADC[i], count);
            }
        count++; 
        }
        check_time_freq = 0;
        flag_adc_volt = 0;
        total_value_offset(adc_vol, vol_offset_sum, count, sizeof(channel_ADC), vol_offset);
        read_integral_voltage(adc_vol, vol_offset, count, sizeof(channel_ADC), vol_sq_sum,  rms_volt);
               
        /*VrmsU_N Calculation*/
        *rms_voltA = rms_volt[0] + rms_volt[1];
        *rms_voltA = *rms_voltA * VOLTAGE_FACTOR;
        
        /*VrmsV_N Calculation*/
        *rms_voltB = rms_volt[2] + rms_volt[1];
        *rms_voltB = *rms_voltB * VOLTAGE_FACTOR;
        
        /*VrmsW_N Calculation*/
        *rms_voltC = rms_volt[3] + rms_volt[1];
        *rms_voltC = *rms_voltC * VOLTAGE_FACTOR;
}

//quandh
CY_ISR(MY_ISR) {    // interrupt timer 
    timer_count++;
    /*measure frenqueny*/
    if(enable_read_frequency == 1){
        adc_freq = ADC_Read(U_ADC);
//         my_printf("adc_freq: %d\r\n", adc_freq);
        if (vr_index >= 1 ) {
            // Check if old value is equal to current value
            if (adc_freq != arrADC[vr_index - 1]) {
                
                // Save data to newest
                arrADC[vr_index] = adc_freq;
                
                if (vr_index == 4) {

                    if((arrADC[vr_index-3]-arrADC[vr_index-4])>0 && (arrADC[vr_index-2]-arrADC[vr_index-3])>0 &&\
                        (arrADC[vr_index-1]-arrADC[vr_index-2])<0 && (arrADC[vr_index]-arrADC[vr_index-1])<0)
                    {
                        tick_period = over_step + timer_count - temp_period;           
                        temp_period = timer_count;
                        over_step = 0;
                        period = tick_period * INTERRUPT_TIMER;
                        frequency = 1 / period;
                       // avg_freq += frequency; 
                        check_freq ++;
                        if(check_freq == 5){
                           // avg_freq = avg_freq / check_freq;
                            complete_read_frequency = 1;   
                            check_freq = 0;
                        }
                    }
                    // Shift arrADC left 1 inc
                    arrADC[vr_index-4] = arrADC[vr_index-3];
                    arrADC[vr_index-3] = arrADC[vr_index-2];
                    arrADC[vr_index-2] = arrADC[vr_index-1];
                    arrADC[vr_index-1] = arrADC[vr_index];
                                                   
                }
                else {
                    vr_index++;
                }               
            }
        }
        else {
            // Save data to first item
            arrADC[vr_index] = adc_freq;
            vr_index++;
        }
    }

    if(flag_adc_volt == 1){
            check_time_freq++;
    }
        
     
    if(timer_count == 100){
//        Timer_1_Stop();
        over_step = over_step + timer_count; 
        timer_count = 0;
        flag_frequency = 1;
    }
    Timer_1_ClearInterrupt(Timer_1_INTR_MASK_TC);
}



int main(void)
{
    Timer_1_Start(); // Configure and enable timer
    isr_1_StartEx(MY_ISR); // setup timer interrupt sub-routine
    ADC_Start();
    ADC_StartConvert();
    UART_Start();
    CyGlobalIntEnable; /* Enable global interrupts. */
    for(;;)
    {
        enable_read_freq();
        wait_for_read_freq();
        my_printf("frequency %0d.%02d\r\n", (int16)frequency, ((int16)(frequency * 100))%100);
        start_read_adc();
        RMS_Voltage_Phase(&rms_voltP1, &rms_voltP2, &rms_voltP3);
        RMS_Current(&rms_curPA);
        
//        rms_volt = ADC_CountsTo_mVolts(0,rms_volt);
        
//        my_printf("count:%d\r\n", count);
//        my_printf("adc_volU[0]: %d\r\n", adc_volU[0]);
//        my_printf("adc_volU[count-1]: %d\r\n", adc_volU[count-1]);
//        my_printf("volU_offset_sum: %d\r\n", volU_offset_sum);
//        my_printf("volU_offset: %d\r\n", volU_offset);
//        my_printf("volU_sq_sum: %d\r\n", volU_sq_sum);
//        my_printf("rms_voltU %0d.%02d\r\n\r\n", (int16)rms_voltU, ((int16)(rms_voltU * 100))%100);
        
        my_printf("rms_voltP1 %0d.%02d\r\n", (int16)rms_voltP1, ((int16)(rms_voltP1 * 100))%100);
        my_printf("rms_voltP2 %0d.%02d\r\n", (int16)rms_voltP2, ((int16)(rms_voltP2 * 100))%100);
        my_printf("rms_voltP3 %0d.%02d\r\n\r\n", (int16)rms_voltP3, ((int16)(rms_voltP3 * 100))%100);
        
        my_printf("rms_voltG1 %0d.%02d\r\n", (int16)rms_voltG1, ((int16)(rms_voltG1 * 100))%100);
        my_printf("rms_voltG2 %0d.%02d\r\n", (int16)rms_voltG2, ((int16)(rms_voltG2 * 100))%100);
        my_printf("rms_voltG3 %0d.%02d\r\n\r\n", (int16)rms_voltG3, ((int16)(rms_voltG3 * 100))%100);
        
        my_printf("rms_curPA %0d.%02d\r\n", (int16)rms_curPA, ((int16)(rms_curPA * 100))%100);
        my_printf("power_factor %0d.%02d\r\n\r\n", (int16)power_factor, ((int16)(power_factor * 100))%100);
        
//        my_printf("adc_curr[0]: %d\r\n", adc_cur[0]);
//        my_printf("adc_curr[count-1]: %d\r\n", adc_cur[count-1]);
//        my_printf("cur_offset_sum: %d\r\n", cur_offset_sum);
//        my_printf("cur_offset: %d\r\n", cur_offset);
//        my_printf("cur_sq_sum: %d\r\n", cur_sq_sum);
//        my_printf("rms_cur %0d.%02d\r\n", (int16)rms_cur, ((int16)(rms_cur * 100))%100);
        
//        for(uint16 i = 0 ; i < count; i++){
//            my_printf("adc_vol[i]: %d\r\n", adc_vol[i]);
////            my_printf("adc_cur[i]: %d\r\n", adc_cur[i]);
//        }
        
        CyDelay(1000);
        
//        my_printf("quan\r\n");
//        CyDelay(1000);
//        LED_Write(~LED_Read());
    }
}

/* [] END OF FILE */
