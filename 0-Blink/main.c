/* 
 * Author: Mahmoud Ahmed 
 * Date: 20 Aug, 2024
 *
 * Target: PY32F002Ax5
 * Project name: Blink
 * Description: This is Blink Code for PA1 --> P5 in breakout board 
*/

#include <py32f0xx.h>

void delay(uint32_t nTime);

int main(void)
{
		/* RCC Clock enable for GPIOA */
		SET_BIT(RCC->IOPENR, RCC_IOPENR_GPIOAEN);
		
		/* Set Pin PA1 as OUTPUT (MODE = 01) */
		MODIFY_REG(GPIOA->MODER, GPIO_MODER_MODE1_1, GPIO_MODER_MODE1_0);
	
		while(1)
		{
			/* Set The PA1 pin, Turn on the LED */
			SET_BIT(GPIOA->BSRR, GPIO_BSRR_BS1);
			delay(0x3FFFF);
			
			/* Reset The PA1 pin, Turn off the LED */
			SET_BIT(GPIOA->BSRR, GPIO_BSRR_BR1);
			delay(0x3FFFF);
		}
}

void delay(uint32_t nTime)
{
		while(nTime--);
}
