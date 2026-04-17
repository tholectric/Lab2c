/*
 * ECE 153B
 *
  * Name(s): Thomas Meza, Shanquin Chen
 * Section: Monday 6:00 PM
 * Lab: 2C
 */
 
#include "stm32l476xx.h"

#include "LED.h"
#include "RTC.h"
#include "SysClock.h"


char strTime[20] = {0};
char strDate[20] = {0};

void RTC_Set_Alarm(void) {
	RTC -> CR &= ~(RTC_CR_ALRAIE|RTC_CR_ALRBIE);
	RTC_Disable_Write_Protection();
	RTC -> CR &= ~(RTC_CR_ALRAE|RTC_CR_ALRBE);
	RTC -> CR &= ~(RTC_CR_ALRAIE|RTC_CR_ALRBIE);
	while(((RTC->ISR & RTC_ISR_ALRAWF) == 0) && ((RTC->ISR & RTC_ISR_ALRBWF) == 0));
	
	
	RTC -> ALRMAR = 0;
	RTC -> ALRMAR |= 0x30;
	RTC -> ALRMAR |= (RTC_ALRMAR_MSK2|RTC_ALRMAR_MSK3|RTC_ALRMAR_MSK4);
	RTC -> ALRMAR &= ~(RTC_ALRMAR_MSK1);
	
	RTC -> ALRMBR = 0;
	RTC -> ALRMBR |= 0x01;
	RTC -> ALRMBR |= (RTC_ALRMBR_MSK2|RTC_ALRMBR_MSK3|RTC_ALRMBR_MSK4|RTC_ALRMBR_MSK1);
	
	RTC -> CR |= (RTC_CR_ALRAE|RTC_CR_ALRBE);
	RTC -> CR |= (RTC_CR_ALRAIE|RTC_CR_ALRBIE);
	RTC_Enable_Write_Protection();
	
}

void RTC_Alarm_Enable(void) {
	EXTI -> RTSR1 |= EXTI_RTSR1_RT18;

	EXTI -> IMR1 |= EXTI_IMR1_IM18;
	
	EXTI -> EMR1 |= EXTI_EMR1_EM18;

	EXTI -> PR1 |= EXTI_PR1_PIF18;
	
	NVIC_EnableIRQ(RTC_Alarm_IRQn);
	NVIC_SetPriority(RTC_Alarm_IRQn, 0);
}

void RTC_Alarm_IRQHandler(void) {
	if ((EXTI -> PR1 & EXTI_PR1_PIF18) != 0){
		
		if (RTC -> ISR & RTC_ISR_ALRAF) {
			// Green_LED_Toggle();
		}
		
		else if (RTC -> ISR & RTC_ISR_ALRBF){
			Green_LED_Toggle();
		}
		RTC->ISR &= ~(RTC_ISR_ALRAF | RTC_ISR_ALRBF);
		EXTI->PR1 |= EXTI_PR1_PIF18;

	}
	// [TODO]
}

int main(void) {	
	LED_Init();
	System_Clock_Init(); // Switch System Clock = 80 MHz
	RTC_Init();
	RTC_Alarm_Enable();
	RTC_Set_Alarm();
	
	while(1) {
		Get_RTC_Calendar(strTime,strDate);
	}
}
