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
#define CURRENT_RATIO      0.0003787
#define U_ADC               0
#define N_ADC               1
#define V_ADC               2
#define W_ADC               3
#define X1_ADC              4
#define L3_ADC              5
#define NL_ADC              6
#define I3_ADC              7

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

void complete_read_freq(){
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

void RMS_Voltage_Phase(float *rms_voltA, float *rms_voltB, float *rms_voltC, float *rms_gridA, float *rms_gridB, float *rms_gridC, float *rms_curA, float *pf){
    int16 adc_volU[500], adc_volN[500], adc_volV[500], adc_volW[500], adc_volL1[500], adc_volL2[500], adc_volL3[500], adc_volNL[500];
    int16  adc_curA[500];
    int32 volU_sq_sum = 0, volV_sq_sum = 0, volW_sq_sum = 0, volN_sq_sum = 0, volL1_sq_sum = 0, volL2_sq_sum = 0, volL3_sq_sum = 0, volNL_sq_sum = 0;
    int32  curA_sq_sum = 0;
    int16 volU_offset = 0, volV_offset = 0, volW_offset = 0, volN_offset = 0, volL1_offset = 0, volL2_offset = 0, volL3_offset = 0, volNL_offset = 0;
    int16 curA_offset = 0;
    int32 volU_offset_sum = 0, volV_offset_sum = 0, volW_offset_sum = 0, volN_offset_sum = 0, volL1_offset_sum = 0, volL2_offset_sum = 0, volL3_offset_sum = 0 ,volNL_offset_sum = 0;
    int32 curA_offset_sum = 0;
    float rms_voltU = 0, rms_voltV = 0, rms_voltW = 0, rms_voltN = 0, rms_voltL1 = 0, rms_voltL2 = 0, rms_voltL3 = 0, rms_voltNL = 0;
    uint16 count = 0;
    while(check_time_freq < tick_period){
            adc_volU[count] = ADC_Read(U_ADC);
            adc_volN[count] = ADC_Read(N_ADC);
            adc_volV[count] = ADC_Read(V_ADC);
            adc_volW[count] = ADC_Read(W_ADC);
            
            select_mux_pin(0, 0, 0);
            adc_volL1[count] = ADC_Read(X1_ADC);
            select_mux_pin(0, 0, 1);
            adc_volL2[count] = ADC_Read(X1_ADC);
            
            adc_volL3[count] = ADC_Read(L3_ADC);
            adc_volNL[count] = ADC_Read(NL_ADC);
            adc_curA[count] = ADC_Read(I3_ADC);
                
            volU_offset_sum += adc_volU[count];
            volN_offset_sum += adc_volN[count]; 
            volV_offset_sum += adc_volV[count];
            volW_offset_sum += adc_volW[count];
            
            volL1_offset_sum += adc_volL1[count];
            volL2_offset_sum += adc_volL2[count];
            volL3_offset_sum += adc_volL3[count];
            volNL_offset_sum += adc_volNL[count];
            
            curA_offset_sum += adc_curA[count];
            
//            cur_offset_sum += adc_cur[count];
            count++; 
        }
        check_time_freq = 0;
        flag_adc_volt = 0;
        volU_offset = volU_offset_sum/count;
        volN_offset = volN_offset_sum/count;
        volV_offset = volV_offset_sum/count;
        volW_offset = volW_offset_sum/count;
    
        volL1_offset = volL1_offset_sum/count;
        volL2_offset = volL2_offset_sum/count;
        volL3_offset = volL3_offset_sum/count;
        volNL_offset = volNL_offset_sum/count;
        curA_offset = curA_offset_sum/count;
       
        for(int i=0;i<count;i++)
        {
            adc_volU[i] = adc_volU[i] - volU_offset;
            adc_volN[i] = adc_volN[i] - volN_offset;
            adc_volV[i] = adc_volV[i] - volV_offset;
            adc_volW[i] = adc_volW[i] - volW_offset;
            
            adc_volL1[i] = adc_volL1[i] - volL1_offset;
            adc_volL2[i] = adc_volL2[i] - volL2_offset;
            adc_volL3[i] = adc_volL3[i] - volL3_offset;
            adc_volNL[i] = adc_volNL[i] - volNL_offset;
            adc_curA[i] = adc_curA[i] - curA_offset;
            
            volU_sq_sum = volU_sq_sum + adc_volU[i] * adc_volU[i];
            volN_sq_sum = volN_sq_sum + adc_volN[i] * adc_volN[i];
            volV_sq_sum = volV_sq_sum + adc_volV[i] * adc_volV[i];
            volW_sq_sum = volW_sq_sum + adc_volW[i] * adc_volW[i];
            
            volL1_sq_sum = volL1_sq_sum + adc_volL1[i] * adc_volL1[i];
            volL2_sq_sum = volL2_sq_sum + adc_volL2[i] * adc_volL2[i];
            volL3_sq_sum = volL3_sq_sum + adc_volL3[i] * adc_volL3[i];
            volNL_sq_sum = volNL_sq_sum + adc_volNL[i] * adc_volNL[i];
            curA_sq_sum = curA_sq_sum + adc_curA[i] * adc_curA[i];
            real_power = real_power + adc_volU[i] * adc_curA[i];
        }
               
        /*VrmsU Calculation*/
        volU_sq_sum = volU_sq_sum/count;
        rms_voltU = sqrt(volU_sq_sum);
        
        /*VrmsN Calculation*/
        volN_sq_sum = volN_sq_sum/count;
        rms_voltN = sqrt(volN_sq_sum);
        
        /*VrmsV Calculation*/
        volV_sq_sum = volV_sq_sum/count;
        rms_voltV = sqrt(volV_sq_sum);
        
        /*VrmsW Calculation*/
        volW_sq_sum = volW_sq_sum/count;
        rms_voltW = sqrt(volW_sq_sum);
        
        /*VrmsL1 Calculation*/
        volL1_sq_sum = volL1_sq_sum/count;
        rms_voltL1 = sqrt(volL1_sq_sum);
        
        /*VrmsL2 Calculation*/
        volL2_sq_sum = volL2_sq_sum/count;
        rms_voltL2 = sqrt(volL2_sq_sum);
        
        /*VrmsL3 Calculation*/
        volL3_sq_sum = volL3_sq_sum/count;
        rms_voltL3 = sqrt(volL3_sq_sum);
        
        /*VrmsNL Calculation*/
        volNL_sq_sum = volNL_sq_sum/count;
        rms_voltNL = sqrt(volNL_sq_sum);
        
        /*RmsIA Calculation*/
        curA_sq_sum = curA_sq_sum / count;
        *rms_curA = sqrt(curA_sq_sum);
        
        /*Power Factor calculation*/
        real_power = real_power / count;
        *pf = real_power/(rms_voltU * (*rms_curA));
        
        /*VrmsU_N Calculation*/
        *rms_voltA = rms_voltU + rms_voltN;
        *rms_voltA = *rms_voltA * VOLTAGE_FACTOR;
        
        /*VrmsV_N Calculation*/
        *rms_voltB = rms_voltV + rms_voltN;
        *rms_voltB = *rms_voltB * VOLTAGE_FACTOR;
        
        /*VrmsW_N Calculation*/
        *rms_voltC = rms_voltW + rms_voltN;
        *rms_voltC = *rms_voltC * VOLTAGE_FACTOR;
        
        /*VrmsL1_NL Calculation*/
        *rms_gridA = rms_voltL1 + rms_voltNL;
        *rms_gridA = *rms_gridA * VOLTAGE_FACTOR;
        
        /*VrmsL2_NL Calculation*/
        *rms_gridB = rms_voltL2 + rms_voltNL;
        *rms_gridB = *rms_gridB * VOLTAGE_FACTOR;
        
        /*VrmsL3_NL Calculation*/
        *rms_gridC = rms_voltL3 + rms_voltNL;
        *rms_gridC = *rms_gridC * VOLTAGE_FACTOR;
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
        complete_read_freq();
        my_printf("frequency %0d.%02d\r\n", (int16)frequency, ((int16)(frequency * 100))%100);
        start_read_adc();
        RMS_Voltage_Phase(&rms_voltP1, &rms_voltP2, &rms_voltP3, &rms_voltG1, &rms_voltG2, &rms_voltG3, &rms_curPA, &power_factor);
        RMS_Current(&rms_curPA);
        /*Irms Calculation*/
//        cur_sq_sum = cur_sq_sum/count;
//        rms_cur = sqrt(cur_sq_sum);
        
        
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
//        MUX_A_Write(1);
        CyDelay(1000);
//        MUX_A_Write(0);
//        CyDelay(1000);
        
//        my_printf("quan\r\n");
//        CyDelay(1000);
//        LED_Write(~LED_Read());
    }
}

/* [] END OF FILE */
