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

// read ADC
int ADC_Read(uint8 chan){
    int32 vrADC;
    while(!ADC_IsEndConversion(ADC_RETURN_STATUS)){};
        vrADC = ADC_CountsTo_mVolts(chan,ADC_GetResult16(chan));
//       vrADC = ADC_GetResult16(chan);
    return vrADC;
}
/* [] END OF FILE */
