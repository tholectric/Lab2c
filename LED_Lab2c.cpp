/*
 * ECE 153B
 *
 * Name(s): Thomas Meza, Shanquin Chen
 * Section: Monday 6:00 PM
 * Lab: 2C
 */

#include "LED.h"

void LED_Init(void) {
	// Enable GPIO Clocks
	// [TODO]
	RCC -> AHB2ENR |= (RCC_AHB2ENR_GPIOAEN | RCC_AHB2ENR_GPIOCEN);
	
	
	// Initialize Green LED
	// [TODO]
	GPIOA -> MODER &= ~(GPIO_MODER_MODER5);
	GPIOA -> MODER |= GPIO_MODER_MODER5_0;
	GPIOA -> OTYPER &= ~GPIO_OTYPER_OT5;
	GPIOA -> PUPDR &= ~GPIO_PUPDR_PUPD5;

}

void Green_LED_Off(void) {
	GPIOA-> ODR &= ~GPIO_ODR_OD5;
}

void Green_LED_On(void) {
	GPIOA -> ODR |= GPIO_ODR_OD5;
}

void Green_LED_Toggle(void) {
	GPIOA -> ODR ^= GPIO_ODR_OD5;
}
